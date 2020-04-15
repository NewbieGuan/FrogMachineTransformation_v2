// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 TRANSFORM_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// TRANSFORM_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef TRANSFORM_EXPORTS
#define TRANSFORM_API __declspec(dllexport)
#else
#define TRANSFORM_API __declspec(dllimport)
#endif

#ifndef TRANSFORM_DLL
#define TRANSFORM_DLL

#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm> 
#include <vector>
#include <armadillo>

using std::ifstream;
using std::ofstream;
using std::runtime_error;
using std::string;
using std::vector;


//坐标值
struct TRANSFORM_API CoordValue
{
	CoordValue() = default;
	CoordValue(double x, double y, double z) :x(x), y(y), z(z) {}
	double x;
	double y;
	double z;
};

//铣床参数
struct TRANSFORM_API MMach
{
	MMach(double L1, double L2, double L3, double L4) :L1(L1), L2(L2), L3(L3), L4(L4) {}
	double L1;
	double L2;
	double L3;
	double L4;
};

//偏置参数
struct TRANSFORM_API Offset
{
	Offset(double Xw, double Yw, double Zw, double Xm, double Ym, double Zm) :
		Xw(Xw), Yw(Yw), Zw(Zw), Xm(Xm), Ym(Ym), Zm(Zm) {}
	//工件坐标系偏置
	double Xw;
	double Yw;
	double Zw;
	//机床偏置
	double Xm;
	double Ym;
	double Zm;
};

//刀具参数
struct TRANSFORM_API Tool
{
	Tool(double Lc, double R, int direction, bool angle_head = false, double La1 = 0, double La2 = 0) :
		Lc(Lc), R(R), direction(direction), angle_head(angle_head), La1(La1), La2(La2) {}
	double Lc;//刀具长
	double R;//刀具半径
	int direction;//刀补方向
	bool angle_head = false;//是否有角铣头
	double La1;//角铣头参数一
	double La2;//角铣头参数二
};

//原坐标转换为新坐标
TRANSFORM_API CoordValue CalcCoord(CoordValue coordvalue, MMach mmach, Offset offset, Tool tool,
	double A, double C, bool command_mode);


//错误类型
enum TRANSFORM_API ErrorType
{
	no_error,    //无错误
	workpiece_error,   //工件坐标系输入错误，工件坐标系范围为54-59！
	sourcefile_error,    //源文件打开失败，请检查路径或是否已打开
	finalfile_error,    //生成文件创建失败，请检查路径
	str_start_error,    //字符串初始位错误,命令行必须以字母开头！
	direction_error,    //刀补方向命令错误，刀补方向命令参数为1或-1！
	angle_head_error,    //有无直角铣头命令错误，角铣头命令参数为0或1！
	parameter_lack_error,    //缺少参数错误，缺少必要参数！\n(请注意绝对坐标模式下第一组坐标是否写全)
	AC_error,   //A/C轴参数错误，A/C轴旋转角度不能为90°或270°！
};


//原文件转换为新文件
TRANSFORM_API ErrorType TransformFile(const string source_file, const string final_file, MMach mmach, Offset offset, const int G_workpiece);

#endif
