#include "FrogMachineTransformation.h"
#include "ui_FrogMachineTransformation.h"
        
using namespace arma;
QString keypath;

constexpr double PI = 3.14159265359;

//构造函数
FrogMachineTransformation::FrogMachineTransformation(QWidget *parent)
	: QMainWindow(parent),ui(new Ui::FrogMachineTransformationClass)
{
	ui->setupUi(this);
	iniUI();
}


//析构函数
FrogMachineTransformation::~FrogMachineTransformation()
{
	delete ui;
}


//初始化函数
void FrogMachineTransformation::iniUI()
{
	ui->dSB_La1->setEnabled(false);
	ui->dSB_La2->setEnabled(false);
	get_machine_data();
	iniSignalSlots();
	iniParameter();

	information = new QLabel;
	information->setText("长度单位:毫米(mm)   角度单位:度(°)  ");
	ui->statusBar->addWidget(information);

	//初始化密码文件的路径
	keypath = QCoreApplication::applicationDirPath();
	QString path_key = "/Setting/Key.ini";
	keypath = keypath + path_key;
}


//初始化ToolButton说明
void FrogMachineTransformation::iniParameter()
{
	parameter_1 = new QLabel(this);
	QPixmap image_1(qApp->applicationDirPath() + "/images/image_1.bmp");
	//QPixmap fit_image_1 = image_1.scaled(584, 446, Qt::KeepAspectRatioByExpanding);
	parameter_1->setPixmap(image_1);
	parameter_1->resize(584, 446);
	parameter_1->hide();
	ui->tB_1->installEventFilter(this);

	parameter_2 = new QLabel(this);
	QPixmap image_2(qApp->applicationDirPath() + "/images/image_2.bmp");
	//QPixmap fit_image_2 = image_2.scaled(548, 345, Qt::KeepAspectRatioByExpanding);
	parameter_2->setPixmap(image_2);
	parameter_2->resize(548, 345);
	parameter_2->hide();
	ui->tB_2->installEventFilter(this);

	parameter_3 = new QLabel(this);
	QPixmap image_3(qApp->applicationDirPath() + "/images/image_3.bmp");
	//QPixmap fit_image_3 = image_3.scaled(538, 506, Qt::KeepAspectRatioByExpanding);
	parameter_3->setPixmap(image_3);
	parameter_3->resize(538, 506);
	parameter_3->hide();
	ui->tB_3->installEventFilter(this);

	parameter_4 = new QLabel(this);
	QPixmap image_4(qApp->applicationDirPath() + "/images/image_4.bmp");
	//QPixmap fit_image_4 = image_4.scaled(399, 143, Qt::KeepAspectRatioByExpanding);
	parameter_4->setPixmap(image_4);
	parameter_4->resize(399, 143);
	parameter_4->hide();
	ui->tB_4->installEventFilter(this);

	parameter_5 = new QLabel(this);
	QPixmap image_5(qApp->applicationDirPath() + "/images/image_5.bmp");
	//QPixmap fit_image_5 = image_5.scaled(359, 77, Qt::KeepAspectRatioByExpanding);
	parameter_5->setPixmap(image_5);
	parameter_5->resize(373, 364);
	parameter_5->hide();
	ui->tB_5->installEventFilter(this);
}


//重写过滤器
bool FrogMachineTransformation::eventFilter(QObject *object, QEvent *event)
{
	if (ui->tB_1 == object)
	{
		if (QEvent::Enter == event->type()) //鼠标进入
		{
			if (parameter_1->isHidden()) //已经隐藏就显示出来
			{ 
				parameter_1->show();
				QPoint point1 = ui->tB_1->mapTo(ui->centralWidget, QPoint(0, 0));
				point1.rx() = point1.x() + ui->tB_1->width() + 15;
				point1.ry() = point1.y();
				parameter_1->move(point1);
				parameter_1->raise();//显示最顶层
				return true;
			}
		}
		else if (QEvent::Leave == event->type()) //鼠标离开
		{ 
			if (!parameter_1->isHidden()) 
			{
				parameter_1->hide();
				return true;
			}
		}
	}

	else if (ui->tB_2 == object)
	{
		if (QEvent::Enter == event->type()) //鼠标进入
		{
			if (parameter_2->isHidden()) //已经隐藏就显示出来
			{
				parameter_2->show();
				QPoint point2 = ui->tB_2->mapTo(ui->centralWidget, QPoint(0, 0));
				point2.rx() = point2.x() + ui->tB_2->width() + 15;
				point2.ry() = point2.y() - 120;
				parameter_2->move(point2);
				parameter_2->raise();//显示最顶层
				return true;
			}
		}
		else if (QEvent::Leave == event->type()) //鼠标离开
		{
			if (!parameter_2->isHidden())
			{
				parameter_2->hide();
				return true;
			}
		}
	}

	else if (ui->tB_3 == object)
	{
		if (QEvent::Enter == event->type()) //鼠标进入
		{
			if (parameter_3->isHidden()) //已经隐藏就显示出来
			{
				parameter_3->show();
				QPoint point3 = ui->tB_3->mapTo(ui->centralWidget, QPoint(0, 0));
				point3.rx() = point3.x() - parameter_3->width() - 15;
				point3.ry() = point3.y() - 50;
				parameter_3->move(point3);
				parameter_3->raise();//显示最顶层
				return true;
			}
		}
		else if (QEvent::Leave == event->type()) //鼠标离开
		{
			if (!parameter_3->isHidden())
			{
				parameter_3->hide();
				return true;
			}
		}
	}

	else if (ui->tB_4 == object)
	{
		if (QEvent::Enter == event->type()) //鼠标进入
		{
			if (parameter_4->isHidden()) //已经隐藏就显示出来
			{
				parameter_4->show();
				QPoint point4 = ui->tB_4->mapTo(ui->centralWidget, QPoint(0, 0));
				point4.rx() = point4.x() - parameter_4->width() - 15;
				point4.ry() = point4.y();
				parameter_4->move(point4);
				parameter_4->raise();//显示最顶层
				return true;
			}
		}
		else if (QEvent::Leave == event->type()) //鼠标离开
		{
			if (!parameter_4->isHidden())
			{
				parameter_4->hide();
				return true;
			}
		}
	}

	else if (ui->tB_5 == object)
	{
		if (QEvent::Enter == event->type()) //鼠标进入
		{
			if (parameter_5->isHidden()) //已经隐藏就显示出来
			{
				parameter_5->show();
				QPoint point5 = ui->tB_5->mapTo(ui->centralWidget, QPoint(0, 0));
				point5.rx() = point5.x() - parameter_5->width() - 15;
				point5.ry() = point5.y();
				parameter_5->move(point5);
				parameter_5->raise();//显示最顶层
				return true;
			}
		}
		else if (QEvent::Leave == event->type()) //鼠标离开
		{
			if (!parameter_5->isHidden())
			{
				parameter_5->hide();
				return true;
			}
		}
	}

	return QWidget::eventFilter(object, event);
}


//信号与槽的连接
void FrogMachineTransformation::iniSignalSlots()
{
	
}


//获取机床数据路径
inline void FrogMachineTransformation::get_data_path()
{
	dirpath = QCoreApplication::applicationDirPath();
	QString filename = "machine_information.txt";
	QDir dir(dirpath);
	if (!dir.exists("data"))
	{
		dir.mkdir("data");
	}
	dir = dirpath.append("/data");
	dirpath = dir.filePath(filename);
}


//打开数据文件初始化comboBox
void FrogMachineTransformation::inicomboBox()
{
	QFile aFile(dirpath);
	aFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream aStream(&aFile);
	machines.clear();
	ui->cbB_Machine->clear();
	while (!aStream.atEnd())
	{
		QString str = aStream.readLine();
		QString str0 = str.section("#$#", 0, 0);
		QString str1 = str.section("#$#", 1, 1);
		QString str2 = str.section("#$#", 2, 2);
		QString str3 = str.section("#$#", 3, 3);
		QString str4 = str.section("#$#", 4, 4);
		double k1 = str1.toDouble();
		double k2 = str2.toDouble();
		double k3 = str3.toDouble();
		double k4 = str4.toDouble();
		Machine_data M1 = { k1,k2,k3,k4 };
		machines.insert(str0, M1);
	}
	aFile.close();
	foreach(const QString &str, machines.keys())
		ui->cbB_Machine->addItem(str, QVariant::fromValue<Machine_data>(machines.value(str)));
}


//初始化comboBox并显示第一项
void FrogMachineTransformation::get_machine_data()
{
	//获取机床数据文件路径
	get_data_path();

	//初始化comboBox
	inicomboBox();

	//显示comboBox第一项数据
	if (!machines.isEmpty())
	{
		Machine_data first_machine = machines.value(machines.firstKey());
		QString K1 = QString::number(first_machine.l1, 'f', 3);
		QString K2 = QString::number(first_machine.l2, 'f', 3);
		QString K3 = QString::number(first_machine.l3, 'f', 3);
		QString K4 = QString::number(first_machine.l4, 'f', 3);
		ui->lineEdit_L1->setText(K1);
		ui->lineEdit_L2->setText(K2);
		ui->lineEdit_L3->setText(K3);
		ui->lineEdit_L4->setText(K4);
	}
	else
	{
		ui->lineEdit_L1->setText(" ");
		ui->lineEdit_L2->setText(" ");
		ui->lineEdit_L3->setText(" ");
		ui->lineEdit_L4->setText(" ");
	}
}


//更新机床数据文件内容
void FrogMachineTransformation::update_data()
{
	QFile aFile(dirpath);
	aFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream aStream(&aFile);
	ui->cbB_Machine->clear();
	QString str_all;
	foreach(const QString &str_name, machines.keys())
	{
		QString str_l1 = QString::number(machines.value(str_name).l1, 'f', 3);
		QString str_l2 = QString::number(machines.value(str_name).l2, 'f', 3);
		QString str_l3 = QString::number(machines.value(str_name).l3, 'f', 3);
		QString str_l4 = QString::number(machines.value(str_name).l4, 'f', 3);
		str_all = str_name + "#$#" + str_l1 + "#$#" + str_l2 + "#$#" + str_l3 + "#$#" + str_l4 + "\n";
		aStream << str_all;
	}
	aFile.close();
}


//弹出密码框并判断密码是否正确 0：错误 1：正确 2：取消
int FrogMachineTransformation::is_pw_correct()
{
	//弹出输入密码对话框
	Dialog_password *enter_pw = new Dialog_password(this);
	Qt::WindowFlags flags = enter_pw->windowFlags();
	enter_pw->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
	int ret = enter_pw->exec();

	//点击取消返回2
	if (ret == QDialog::Rejected)
		return 2;

	//判断密码是否输入正确
	QFile aFile(keypath);
	aFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream aStream(&aFile);
	QString true_password = aStream.readLine();
	aFile.close();

	QString password = enter_pw->get_password();
	if (true_password == password.trimmed())
		return 1;
	else
		return 0;
}


//添加项
void FrogMachineTransformation::on_pB_add_clicked()
{
	//弹出密码框并判断密码是否正确
	int parameter_pw = is_pw_correct();
	//0：错误
	if (parameter_pw == 0)
	{
		QString dlgTitle = "密码错误";
		QString strInfo = "密码错误，请重试！";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}
	//1：正确
	else if (parameter_pw == 1)
	{
		//获得当前项
		QString current_Item = ui->cbB_Machine->currentText();

		//创建对话框
		Dialog_add *addItem = new Dialog_add(this);
		Qt::WindowFlags flags = addItem->windowFlags();
		addItem->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
		int ret = addItem->exec();

		//如果收到确认信号
		if (ret == QDialog::Accepted)
		{
			//先判断有没有重名
			QString name = addItem->get_name();
			if (machines.contains(name))
			{
				QString dlgTitle = "警告";
				QString strInfo = "已有同名项";
				QMessageBox::warning(this, dlgTitle, strInfo);
			}
			else if (name.contains("#$#"))
			{
				QString dlgTitle = "警告";
				QString strInfo = "名称中不能包含\"#$#\"字符";
				QMessageBox::warning(this, dlgTitle, strInfo);
			}
			//将内容添加到数据文档
			else
			{
				//添加新项
				QString new_name = addItem->get_name();
				double k1 = addItem->get_L1();
				double k2 = addItem->get_L2();
				double k3 = addItem->get_L3();
				double k4 = addItem->get_L4();
				Machine_data M1 = { k1,k2,k3,k4 };
				machines.insert(new_name, M1);

				//更新机床数据文件内容
				update_data();

				//另一种添加方式
				/*QString K1 = addItem->get_L1();
				QString K2 = addItem->get_L2();
				QString K3 = addItem->get_L3();
				QString K4 = addItem->get_L4();
				QString gather = name + "#$#" + K1 + "#$#" + K2 + "#$#" + K3 + "#$#" + K4 + "\n";
				get_data_path();
				QFile aFile(dirpath);
				aFile.open(QIODevice::Append | QIODevice::Text);
				QTextStream aStream(&aFile);
				aStream << gather;
				aFile.close();*/

				//打开数据文件初始化comboBox
				inicomboBox();

				//comboBox显示添加项数据
				Machine_data new_machine = machines.value(new_name);
				QString l1 = QString::number(new_machine.l1, 'f', 3);
				QString l2 = QString::number(new_machine.l2, 'f', 3);
				QString l3 = QString::number(new_machine.l3, 'f', 3);
				QString l4 = QString::number(new_machine.l4, 'f', 3);
				ui->cbB_Machine->setCurrentText(new_name);
				ui->lineEdit_L1->setText(l1);
				ui->lineEdit_L2->setText(l2);
				ui->lineEdit_L3->setText(l3);
				ui->lineEdit_L4->setText(l4);
			}
		}
		delete addItem;
	}
}


//修改项
void FrogMachineTransformation::on_pB_amend_clicked()
{
	//弹出密码框并判断密码是否正确
	int parameter_pw = is_pw_correct();
	//0：错误
	if (parameter_pw == 0)
	{
		QString dlgTitle = "密码错误";
		QString strInfo = "密码错误，请重试！";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}
	//1：正确
	else if (parameter_pw == 1)
	{
		//获得当前项
		QString current_Item = ui->cbB_Machine->currentText();
		Machine_data current_machine = machines.value(current_Item);
		double l1 = current_machine.l1;
		double l2 = current_machine.l2;
		double l3 = current_machine.l3;
		double l4 = current_machine.l4;

		//创建对话框
		Dialog_amend *addItem = new Dialog_amend(this);
		Qt::WindowFlags flags = addItem->windowFlags();
		addItem->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
		addItem->setItem(current_Item, l1, l2, l3, l4);//显示当前项
		int ret = addItem->exec();

		//如果收到确认信号
		if (ret == QDialog::Accepted)
		{
			machines.remove(current_Item);//移去旧项
			QString new_name = addItem->get_name();
			double k1 = addItem->get_L1();
			double k2 = addItem->get_L2();
			double k3 = addItem->get_L3();
			double k4 = addItem->get_L4();
			Machine_data M1 = { k1,k2,k3,k4 };
			machines.insert(new_name, M1);//添加新项

			//获取机床数据路径
			get_data_path();

			//更新机床数据文件内容
			update_data();

			//打开数据文件初始化comboBox
			inicomboBox();

			//继续显示comboBox当前项数据
			QString K1 = QString::number(machines.value(new_name).l1, 'f', 3);
			QString K2 = QString::number(machines.value(new_name).l2, 'f', 3);
			QString K3 = QString::number(machines.value(new_name).l3, 'f', 3);
			QString K4 = QString::number(machines.value(new_name).l4, 'f', 3);
			ui->cbB_Machine->setCurrentText(new_name);
			ui->lineEdit_L1->setText(K1);
			ui->lineEdit_L2->setText(K2);
			ui->lineEdit_L3->setText(K3);
			ui->lineEdit_L4->setText(K4);
		}
		delete addItem;
	}
}


//移除项
void FrogMachineTransformation::on_pB_remove_clicked()
{
	//弹出密码框并判断密码是否正确
	int parameter_pw = is_pw_correct();
	//0：错误
	if (parameter_pw == 0)
	{
		QString dlgTitle = "密码错误";
		QString strInfo = "密码错误，请重试！";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}
	//1：正确
	else if (parameter_pw == 1)
	{
		QString dlgTitle = "删除提示";
		QString strInfo = "确认删除此项吗？";
		QMessageBox::StandardButton defaultBtn = QMessageBox::No;
		QMessageBox::StandardButton result;
		result = QMessageBox::question(this, dlgTitle, strInfo,
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, defaultBtn);
		if (result == QMessageBox::Yes)
		{
			//获得当前项
			QString current_Item = ui->cbB_Machine->currentText();

			//移去当前项
			machines.remove(current_Item);

			//判断此时machines是否为空
			if (machines.isEmpty() == false)
			{
				//获取机床数据路径
				get_data_path();

				//更新机床数据文件内容
				update_data();

				//打开数据文件初始化comboBox
				inicomboBox();

				//显示comboBox第一项数据
				Machine_data first_machine = machines.value(machines.firstKey());
				QString K1 = QString::number(first_machine.l1, 'f', 3);
				QString K2 = QString::number(first_machine.l2, 'f', 3);
				QString K3 = QString::number(first_machine.l3, 'f', 3);
				QString K4 = QString::number(first_machine.l4, 'f', 3);
				ui->cbB_Machine->setEditText(machines.firstKey());
				ui->lineEdit_L1->setText(K1);
				ui->lineEdit_L2->setText(K2);
				ui->lineEdit_L3->setText(K3);
				ui->lineEdit_L4->setText(K4);
			}
			else
			{
				ui->cbB_Machine->clear();
				ui->lineEdit_L1->clear();
				ui->lineEdit_L2->clear();
				ui->lineEdit_L3->clear();
				ui->lineEdit_L4->clear();
			}
		}
	}
}


//修改密码
void FrogMachineTransformation::on_pB_password_clicked()
{
	Dialog_change_password *change_pw = new Dialog_change_password(this);
	Qt::WindowFlags flags = change_pw->windowFlags();
	change_pw->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
	int ret = change_pw->exec();

	if (ret == QDialog::Accepted)
		delete change_pw;
}


//下拉列表框改变时
void FrogMachineTransformation::on_cbB_Machine_activated(const QString &arg1)
{
	Machine_data current_machine = machines.value(arg1);
	QString K1 = QString::number(current_machine.l1, 'f', 3);
	QString K2 = QString::number(current_machine.l2, 'f', 3);
	QString K3 = QString::number(current_machine.l3, 'f', 3);
	QString K4 = QString::number(current_machine.l4, 'f', 3);
	ui->lineEdit_L1->setText(K1);
	ui->lineEdit_L2->setText(K2);
	ui->lineEdit_L3->setText(K3);
	ui->lineEdit_L4->setText(K4);
}


//直角铣头复选框被按下
void FrogMachineTransformation::on_cB_head_clicked(bool checked)
{
	ui->dSB_La1->setEnabled(checked);
	ui->dSB_La2->setEnabled(checked);
}


//公用数据初始化
void FrogMachineTransformation::iniShared()
{
	QString str_L1 = ui->lineEdit_L1->text();
	QString str_L2 = ui->lineEdit_L2->text();
	QString str_L3 = ui->lineEdit_L3->text();
	QString str_L4 = ui->lineEdit_L4->text();
	L1 = str_L1.toDouble();
	L2 = str_L2.toDouble();
	L3 = str_L3.toDouble();
	L4 = str_L4.toDouble();
	Xw = ui->dSB_Xw->value();
	Yw = ui->dSB_Yw->value();
	Zw = ui->dSB_Zw->value();
	Xm = ui->dSB_Xm->value();
	Ym = ui->dSB_Ym->value();
	Zm = ui->dSB_Zm->value();
}


//计算按钮被按下
void FrogMachineTransformation::on_pB_cout_clicked()
{
	//判断A/C轴旋转角度是否为90°或270°
	A = ui->dSB_A->value();
	C = ui->dSB_C->value();
	if (A == 90 || A == 270 || C == 90 || C == 270)
	{
		QString dlgTitle = "参数错误";
		QString strInfo = "A/C轴旋转角度不能为90°或270°！";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}
	else
	{
		//获得各项数据
		iniShared();
		Lc = ui->dSB_Lc->value();
		R = ui->dSB_R->value();
		La1 = ui->dSB_La1->value();
		La2 = ui->dSB_La2->value();
		x_1 = ui->dSB_x1->value();
		y_1 = ui->dSB_y1->value();
		z_1 = ui->dSB_z1->value();
		if (ui->cB_head->isChecked())
			angle_head = true;
		else
			angle_head = false;
		if (ui->rB_positive->isChecked())
			direction = true;
		else
			direction = false;
		if (ui->rB_G90->isChecked())
			command_mode = false;
		else
			command_mode = true;

		//得到新坐标
		CoordValue coordvalue(x_1, y_1, z_1);
		MMach mmach(L1, L2, L3, L4);
		Offset offset(Xw, Yw, Zw, Xm, Ym, Zm);
		Tool tool(Lc, R, direction, angle_head, La1, La2);
		CoordValue newPoint = CalcCoord(coordvalue, mmach, offset, tool, A, C, command_mode);

		//显示新坐标s
		ui->dSB_x2->setValue(newPoint.x);
		ui->dSB_y2->setValue(newPoint.y);
		ui->dSB_z2->setValue(newPoint.z);
	}
}


//选择文件按钮被按下
void FrogMachineTransformation::on_pB_openfile_clicked()
{
	dirpath = QCoreApplication::applicationDirPath();
	QString path_setting = "/Setting/Setting_open.ini";
	path_setting = dirpath + path_setting;

	QSettings setting(path_setting, QSettings::IniFormat);//QSettings能记录一些程序中的信息，下次再打开时可以读取出来
	QString lastPath = setting.value("LastFilePath_open").toString();//获取上次的打开路径
	QString dlgTitle = "选择一个文件";
	QString filter = "Siemens程序文件(*.mpf *.spf);;文本文件(*.txt);;所有文件(*.*)";
	//获取文件的路径
	QString filePath = QFileDialog::getOpenFileName(this, dlgTitle, lastPath, filter);//从上次的路径处打开
	if (!filePath.isEmpty())
	{
		setting.setValue("LastFilePath_open", filePath);  //记录路径到QSetting中保存
		ui->lineEdit_filepath->setText(filePath);
	}
}


//文档转换按钮被按下
void FrogMachineTransformation::on_pB_convert_clicked()
{
	//获取工件坐标系
	G_workpiece = ui->sB_workpiece->value();

	//获取源文件路径
	QString SourceFileName = ui->lineEdit_filepath->text();
	QByteArray data1 = SourceFileName.toLocal8Bit();
	string sourceFile(data1);

	//弹出保存文件对话框
	dirpath = QCoreApplication::applicationDirPath();
	QString path_setting = "/Setting/Setting_save.ini";
	path_setting = dirpath + path_setting;
	QSettings setting(path_setting, QSettings::IniFormat);//QSettings能记录一些程序中的信息，下次再打开时可以读取出来
	QString lastPath = setting.value("LastFilePath_save").toString();//获取上次的打开路径
	QString dlgTitle = "选择一个文件";
	QString filter = "Siemens程序文件(*.mpf *.spf);;文本文件(*.txt);;所有文件(*.*)";
	//获取保存文件的路径
	QString SaveFileName = QFileDialog::getSaveFileName(this, dlgTitle, lastPath, filter);//从上次的路径处打开
	if (!SaveFileName.isEmpty())
		setting.setValue("LastFilePath_save", SaveFileName);  //记录路径到QSetting中保存
	QByteArray data2 = SaveFileName.toLocal8Bit();
	string finalFile(data2);

	//获取机床参数和偏置设定
	iniShared();
	MMach mmach(L1, L2, L3, L4);
	Offset offset(Xw, Yw, Zw, Xm, Ym, Zm);

	//文档转换
	enum ErrorType et = TransformFile(sourceFile, finalFile, mmach, offset, G_workpiece);
	QString strInfo;
	switch (et)
	{
	case no_error:
		dlgTitle = "消息提示";
		strInfo = "文档转换成功！";
		QMessageBox::information(this, dlgTitle, strInfo);
		break;
	case workpiece_error:
		dlgTitle = "工件坐标系格式错误";
		strInfo = "工件坐标系范围为54-59！";
		QMessageBox::critical(this, dlgTitle, strInfo);
		break;
	case sourcefile_error:
		dlgTitle = "警告";
		strInfo = "文件不存在！";
		QMessageBox::warning(this, dlgTitle, strInfo);
		break;
	case finalfile_error:
		dlgTitle = "警告";
		strInfo = "保存文件路径错误！";
		QMessageBox::warning(this, dlgTitle, strInfo);
		break;
	case str_start_error:
		dlgTitle = "文件格式错误";
		strInfo = "命令行必须以字母开头！(请注意文件编码格式)";
		QMessageBox::critical(this, dlgTitle, strInfo);
		break;
	case direction_error:
		dlgTitle = "文件格式错误";
		strInfo = "刀补方向命令参数为1或-1！";
		QMessageBox::critical(this, dlgTitle, strInfo);
		break;
	case angle_head_error:
		dlgTitle = "文件格式错误";
		strInfo = "角铣头命令参数为0或1！";
		QMessageBox::critical(this, dlgTitle, strInfo);
		break;
	case parameter_lack_error:
		dlgTitle = "参数错误";
		strInfo = "缺少必要参数！\n(请注意绝对坐标模式下第一组坐标是否写全)";
		QMessageBox::critical(this, dlgTitle, strInfo);
		break;
	case AC_error:
		dlgTitle = "参数错误";
		strInfo = "A/C轴旋转角度不能为90°或270°！";
		QMessageBox::critical(this, dlgTitle, strInfo);
		break;
	default:
		break;
	}
}
