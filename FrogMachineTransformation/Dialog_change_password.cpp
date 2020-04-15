#include "Dialog_change_password.h"
#include "ui_Dialog_change_password.h"

Dialog_change_password::Dialog_change_password(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::Dialog_change_password();
	ui->setupUi(this);
}

Dialog_change_password::~Dialog_change_password()
{
	delete ui;
}

QString Dialog_change_password::get_old_password()
{
	return ui->lineEdit_old_pw->text();
}

QString Dialog_change_password::get_new_password1()
{
	return ui->lineEdit_new_pw1->text();
}

QString Dialog_change_password::get_new_password2()
{
	return ui->lineEdit_new_pw2->text();
}

void Dialog_change_password::on_btn_ok_clicked()
{
	//��ȡ�ļ��е�����
	QFile aFile(keypath);
	aFile.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream aStream(&aFile);
	QString true_password = aStream.readLine();
	aFile.close();

	//�鿴�����Ƿ���ȷ
	QString old_pw = get_old_password();
	QString new_pw1 = get_new_password1();
	QString new_pw2 = get_new_password2();
	if (old_pw.trimmed() != true_password)//�������
	{
		QString dlgTitle = "�������";
		QString strInfo = "ԭ������������ԣ�";
		QMessageBox::critical(this, dlgTitle, strInfo);
	}
	else if (new_pw1.trimmed().isEmpty())
	{
		QString dlgTitle = "����";
		QString strInfo = "�����벻��Ϊ�գ�";
		QMessageBox::warning(this, dlgTitle, strInfo);
	}
	else if (new_pw1.trimmed() != new_pw2.trimmed())//���������벻һ��
	{
		QString dlgTitle = "����";
		QString strInfo = "�������������벻һ�£�";
		QMessageBox::warning(this, dlgTitle, strInfo);
	}
	else//��ȷ���
	{
		QFile aFile(keypath);
		aFile.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream aStream(&aFile);
		aStream << new_pw1.trimmed();
		aFile.close();

		QString dlgTitle = "�޸�����";
		QString strInfo = "�����޸ĳɹ���";
		QMessageBox::information(this, dlgTitle, strInfo);

		accept();
	}
}