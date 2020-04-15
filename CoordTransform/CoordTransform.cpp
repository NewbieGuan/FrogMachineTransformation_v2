// CoordTransform.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "CoordTransform.h"

using std::vector;
using std::runtime_error;
using namespace arma;

constexpr double PI = 3.14159265359;

//原坐标转换为新坐标
TRANSFORM_API CoordValue CalcCoord(CoordValue coordvalue, MMach mmach, Offset offset, Tool tool,
	double A, double C, bool command_mode)
{
	if (A == 90 || A == 270 || C == 90 || C == 270)
		throw runtime_error("A/C轴旋转角度不能为90°或270°！");

	A = A * PI / 180;
	C = C * PI / 180;

	double x_1 = coordvalue.x;
	double y_1 = coordvalue.y;
	double z_1 = coordvalue.z;
	double L1 = mmach.L1;
	double L2 = mmach.L2;
	double L3 = mmach.L3;
	double L4 = mmach.L4;
	double Xw = offset.Xw;
	double Yw = offset.Yw;
	double Zw = offset.Zw;
	double Xm = offset.Xm;
	double Ym = offset.Ym;
	double Zm = offset.Zm;
	double Lc = tool.Lc;
	double R = tool.R;
	int direction = tool.direction;
	bool angle_head = tool.angle_head;
	double La1 = tool.La1;
	double La2 = tool.La2;

	//利用数据创建所需要的矩阵
	Mat<double> T_AB(4, 4);
	T_AB << 1 << 0 << 0 << Xw - Xm - L1 << endr
		<< 0 << 1 << 0 << Yw + L2 + L3 << endr
		<< 0 << 0 << 1 << Zw - L4 << endr
		<< 0 << 0 << 0 << 1 << endr;

	Mat<double> T_BB1(4, 4);
	T_BB1 << cos(C) << sin(C) << 0 << 0 << endr
		<< -sin(C) << cos(C) << 0 << 0 << endr
		<< 0 << 0 << 1 << 0 << endr
		<< 0 << 0 << 0 << 1 << endr;

	Mat<double> T_B1C(4, 4);
	if (angle_head)
	{
		T_B1C << 1 << 0 << 0 << L1 << endr
			<< 0 << 1 << 0 << -(Ym + L2 + L3 / cos(A)) - (L4 + La1 - Zm - L3 * tan(A))*sin(A) - (La2 + Lc)*cos(A) << endr
			<< 0 << 0 << 1 << (L4 + La1 - Zm - L3 * tan(A))*cos(A) - (La2 + Lc)*sin(A) << endr
			<< 0 << 0 << 0 << 1 << endr;
	}
	else
	{
		T_B1C << 1 << 0 << 0 << L1 << endr
			<< 0 << 1 << 0 << -(Ym + L2 + L3 / cos(A)) - (L4 + Lc - Zm - L3 * tan(A))*sin(A) << endr
			<< 0 << 0 << 1 << (L4 + Lc - Zm - L3 * tan(A))*cos(A) << endr
			<< 0 << 0 << 0 << 1 << endr;
	}

	Mat<double> T_CD(4, 4);
	if (angle_head)
	{
		if (direction)
		{
			T_CD << 1 << 0 << 0 << 0 << endr
				<< 0 << 1 << 0 << -R * sin(A) << endr
				<< 0 << 0 << 1 << R * cos(A) << endr
				<< 0 << 0 << 0 << 1 << endr;
		}
		else
		{
			T_CD << 1 << 0 << 0 << 0 << endr
				<< 0 << 1 << 0 << R * sin(A) << endr
				<< 0 << 0 << 1 << -R * cos(A) << endr
				<< 0 << 0 << 0 << 1 << endr;
		}
	}
	else
	{
		if (direction)
		{
			T_CD << 1 << 0 << 0 << 0 << endr
				<< 0 << 1 << 0 << R * cos(A) << endr
				<< 0 << 0 << 1 << R * sin(A) << endr
				<< 0 << 0 << 0 << 1 << endr;
		}
		else
		{
			T_CD << 1 << 0 << 0 << 0 << endr
				<< 0 << 1 << 0 << -R * cos(A) << endr
				<< 0 << 0 << 1 << -R * sin(A) << endr
				<< 0 << 0 << 0 << 1 << endr;
		}
	}

	Mat<double> T_ED(4, 4);
	T_ED << cos(C) << 0 << 0 << 0 << endr
		<< -sin(C) << 1 << -sin(A) << 0 << endr
		<< 0 << 0 << cos(A) << 0 << endr
		<< 0 << 0 << 0 << 1 << endr;

	Mat<double> T_DE(4, 4);
	T_DE = inv(T_ED);

	if (command_mode == false)//G90
	{
		//工件坐标系点坐标
		Mat<double> P1(4, 1);
		P1 << x_1 << endr
			<< y_1 << endr
			<< z_1 << endr
			<< 1 << endr;

		//新坐标系点坐标
		mat P2;
		P2 = T_DE * T_CD * T_B1C * T_BB1 * T_AB * P1;
		CoordValue new_value;
		new_value.x = P2.at(0, 0);
		new_value.y = P2.at(1, 0);
		new_value.z = P2.at(2, 0);
		//double k2 = P2.at(3, 0);

		return new_value;
	}
	else//G91
	{
		Mat<double> P1_diff(4, 1);
		P1_diff << x_1 << endr
			<< y_1 << endr
			<< z_1 << endr
			<< 0 << endr;

		mat P2_diff;
		P2_diff = T_DE * T_CD * T_B1C * T_BB1 * T_AB * P1_diff;
		CoordValue diff_value;
		diff_value.x = P2_diff.at(0, 0);
		diff_value.y = P2_diff.at(1, 0);
		diff_value.z = P2_diff.at(2, 0);
		//double k2 = P2_diff.at(3, 0);

		return diff_value;
	}
}


/*
La1：直角铣头的Z方向长度。
La2：直角铣头的Y方向长度。
Lc：刀具长度。
R：新坐标系下使用的刀具半径。
A：A轴旋转角度。
C：C轴旋转角度。
x_1：工件坐标系下的X轴坐标值或增量。
y_1：工件坐标系下的Y轴坐标值或增量。
z_1：工件坐标系下的Z轴坐标值或增量。
*/
double La1, La2, Lc, R, A, C, x_1, y_1, z_1;

//错误类型
enum ErrorType error_type;
//各种参数状态位
bool state_A, state_C, state_Lc, state_R, state_direction, state_angle_head, state_La1, state_La2,
state_x1, state_y1, state_z1, state_workpiece;
bool angle_head, direction, command_mode;

//错误标志及参数状态位初始化
void ini_state()
{
	error_type = no_error;
	angle_head = false;
	direction = false;
	command_mode = false;
	
	state_A = false;
	state_C = false;
	state_Lc = false;
	state_R = false;
	state_direction = false;
	state_angle_head = false;
	state_La1 = false;
	state_La2 = false;
	state_x1 = false;
	state_y1 = false;
	state_z1 = false;
	state_workpiece = false;
}


//精简字符串
string get_pure_str(string str)
{
	string str_pure = str;
	string str_exclude = ";；#";
	auto index_1 = str_pure.find_first_of(str_exclude);
	//截取
	if (index_1 != string::npos)
		str_pure = str_pure.substr(0, index_1);

	//去空格
	string::size_type index_2 = 0;
	while ((index_2 = str_pure.find(' ', index_2)) != string::npos)
		str_pure.erase(index_2, 1);

	//变大写
	transform(str_pure.begin(), str_pure.end(), str_pure.begin(), ::toupper);

	return str_pure;
}


//检查字符串格式
void check_str(string str)
{
	//判断首字符是不是字母
	if (!(str[0] >= 'A'&&str[0] <= 'Z'))
		error_type = str_start_error;

	//判断目前坐标模式
	if (str.find("G91")!=string::npos)
		command_mode = true;
	if (str.find("G90") != string::npos)
		command_mode = false;
}


//处理CS_字符串并提取信息
string get_CS_str(string str)
{
	string str_out;
	if (str.find("CS_BJ=") == 0)//刀具半径
	{
		string str_R = str.substr(6);
		R = stod(str_R);
		state_R = true;
	}
	else if (str.find("CS_CD=") == 0)//刀具长度
	{
		string str_Lc = str.substr(6);
		Lc = stod(str_Lc);
		state_Lc = true;
	}
	else if (str.find("CS_FX=") == 0)//补偿方向
	{
		string str_direction = str.substr(6);
		int value_direction = stod(str_direction);
		switch (value_direction)
		{
		case 1:direction = true; break;
		case -1:direction = false; break;
		default:error_type = direction_error; break;
		}
		state_direction = true;
	}
	else if (str.find("CS_JXT=") == 0)//角铣头
	{
		string str_angle_head_2 = str.substr(7);
		int value_angle_head_2 = stod(str_angle_head_2);
		switch (value_angle_head_2)
		{
		case 1:angle_head = true; break;
		case 0:angle_head = false; break;
		default:error_type = angle_head_error; break;
		}
		state_angle_head = true;
	}
	else if (str.find("CS_JXTZ=") == 0)//角铣头Z方向长度
	{
		string str_La1 = str.substr(8);
		La1 = stod(str_La1);
		state_La1 = true;
	}
	else if (str.find("CS_JXTY=") == 0)//角铣头Y方向长度
	{
		string str_La2 = str.substr(8);
		La2 = stod(str_La2);
		state_La2 = true;
	}

	str_out = ";" + str;
	return str_out;
}


//字符串分块
vector<string> get_StringList(string str)
{
	//遍历字符串得到字母序号
	vector<int> serial_number;
	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) >= 'A' && str.at(i) <= 'Z')
			serial_number.push_back(i);
	}
	//遍历子字符串获取信息
	vector<string> str_list;
	int number = serial_number.size();
	for (int j = 0; j < number; j++)
	{
		string str_part;
		int begin_posision = serial_number[j];
		if (j < number - 1)
		{
			int part_length = serial_number[j + 1] - serial_number[j];
			str_part = str.substr(begin_posision, part_length);
			str_list.push_back(str_part);
		}
		else
		{
			str_part = str.substr(begin_posision);
			str_list.push_back(str_part);
		}
	}
	return str_list;
}


//处理XYZ字符串
string get_G90_G91_str(string str, MMach mmach, Offset offset, const int G_workpiece)
{
	string str_out;
	//分块得到vector<string>
	vector<string> str_list = get_StringList(str);
	//提取块信息
	for (int i = 0; i < str_list.size(); i++)
	{
		string str_block = str_list[i];
		if (str_block.find("X") == 0)
		{
			string str_x1 = str_block.substr(1);
			x_1 = stod(str_x1);
			state_x1 = true;
		}
		else if (str_block.find("Y") == 0)
		{
			string str_y1 = str_block.substr(1);
			y_1 = stod(str_y1);
			state_y1 = true;
		}
		else if (str_block.find("Z") == 0)
		{
			string str_z1 = str_block.substr(1);
			z_1 = stod(str_z1);
			state_z1 = true;
		}
		else
		{
			str_out.append(str_block);
			str_out.append(" ");
		}
	}

	//判断参数是否足够
	if (state_A && state_C && state_Lc && state_R && state_direction &&
		state_angle_head && state_x1 && state_y1 && state_z1)
	{
		if (angle_head == true)
			if (!(state_La1 == true && state_La2 == true))
				error_type = parameter_lack_error;
	}
	else
		error_type = parameter_lack_error;

	//如果参数足够
	if (error_type == no_error)
	{
		CoordValue coordvalue(x_1, y_1, z_1);
		Tool tool(Lc, R, direction, angle_head, La1, La2);
		CoordValue newPoint = CalcCoord(coordvalue, mmach, offset, tool, A, C, command_mode);

		string str_x2 = std::to_string(floor(newPoint.x * 1000 + 0.5) / 1000);
		str_x2 = str_x2.substr(0, str_x2.size() - 3);
		string str_y2 = std::to_string(floor(newPoint.y * 1000 + 0.5) / 1000);
		str_y2 = str_y2.substr(0, str_y2.size() - 3);
		string str_z2 = std::to_string(floor(newPoint.z * 1000 + 0.5) / 1000);
		str_z2 = str_z2.substr(0, str_z2.size() - 3);
		string str_XYZ = "X" + str_x2 + " " + "Y" + str_y2 + " " + "Z" + str_z2;
		str_out.append(str_XYZ);
	}
	return str_out;
}


//提取块信息
void get_block_info(string &str, const int G_workpiece)
{
	if (str.find("G") == 0)
	{
		string str_G = str.substr(1);
		int G = stoi(str_G);
		if (G > 53 && G < 60)
		{
			if (G == G_workpiece)
				state_workpiece = true;
			else
				state_workpiece = false;
		}
	}
	else if (str.find("A") == 0)
	{
		string str_A = str.substr(1);
		A = stod(str_A);
		state_A = true;
		if (A == 90 || A == 270)
			error_type = AC_error;
	}
	else if (str.find("C") == 0)
	{
		string str_C = str.substr(1);
		C = stod(str_C);
		state_C = true;
		if (C == 90 || C == 270)
			error_type = AC_error;
	}
	else if (str.find("M30") == 0 || str.find("M02") == 0)
	{
		//错误标志及参数状态位初始化
		ini_state();
	}
}


//输入字符串变输出字符串
string str_transform(string str, MMach mmach, Offset offset, const int G_workpiece)
{
	string str_out;
	if (str.find("CS_")!=string::npos)
	{
		str_out = get_CS_str(str);
	}
	else if ((str.find("X") !=string::npos || str.find("Y") != string::npos || str.find("Z") != string::npos) && state_workpiece)
	{
		str_out = get_G90_G91_str(str, mmach, offset, G_workpiece);
	}
	else
	{
		//分块得到vector<string>
		vector<string> str_list = get_StringList(str);
		//提取块信息
		for (int i = 0; i < str_list.size(); i++)
		{
			string str_block = str_list[i];
			get_block_info(str_block, G_workpiece);

			if (i < str_list.size() - 1)
			{
				str_out.append(str_block);
				str_out.append(" ");
			}
			else
			{
				str_out.append(str_block);
			}
		}
	}
	return str_out;
}


//原文件转换为新文件
TRANSFORM_API ErrorType TransformFile(const string source_file, const string final_file, MMach mmach, Offset offset, const int G_workpiece)
{
	//错误标志及参数状态位初始化
	ini_state();
	
	//判断工件坐标系参数输入是否正确
	if (!(G_workpiece > 53 && G_workpiece < 60))
		return workpiece_error;

	//判断源文件路径是否正确或者已经打开
	ifstream sourceFile(source_file, ifstream::in);
	if (!sourceFile)
		return sourcefile_error;

	//判断生成文件路径是否正确
	ofstream finalFile(final_file, ofstream::out);
	if (!sourceFile)
		return finalfile_error;

	//处理文件内容
	string strFinal;
	string str_line;
	while (getline(sourceFile, str_line))
	{
		if (str_line.empty())
			continue;

		//精简字符串
		string str_pure = get_pure_str(str_line);
		if (str_pure.empty())
			continue;

		//检查字符串格式
		check_str(str_pure);
		if (error_type == str_start_error)
			return error_type;

		//得到新字符串
		string str_out = str_transform(str_pure, mmach, offset, G_workpiece);
		if (error_type != no_error)
			return error_type;

		strFinal.append(str_out);
		strFinal.append(1, '\n');
	}

	//保存新文件内容
	finalFile << strFinal << std::endl;
	finalFile.close();
	return error_type;
}
