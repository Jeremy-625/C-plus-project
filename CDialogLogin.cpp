// CDialogLogin.cpp: 实现文件
//

#include "pch.h"
#include "C5.h"
#include "CDialogLogin.h"
#include "afxdialogex.h"

#include <iostream>
#include <fstream>

#include "course.h"
#include "student.h"
using namespace std;

extern Course cou[12];
extern Ugstudent ugstu[30];
extern Gstudent gstu[15];
extern int isg;
extern int order;

// CDialogLogin 对话框

IMPLEMENT_DYNAMIC(CDialogLogin, CDialog)

CDialogLogin::CDialogLogin(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CDialogLogin::~CDialogLogin()
{
}

void CDialogLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CDialogLogin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogLogin::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogLogin::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDialogLogin 消息处理程序


void CDialogLogin::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CDialogLogin::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	int flag;
	int f;
	for (int i = 0; i < 30; i++)
	{
		flag = 0;
		CString user(ugstu[i].getid());
		if (m_user == user)
			if (m_pwd == user)
			{	
				isg = 0;
				order = i;
				CDialog::OnOK();
				break;
			}
			else
				flag = 1;		//密码错误
		else
			flag = 1;			//用户名错误
	}
	for (int i = 0; i < 15; i++)
	{
		f = 0;
		CString user(gstu[i].getid());
		if(m_user==user)
			if (m_pwd == user)
			{
				isg = 1;
				order = i;
				CDialog::OnOK();
				break;
			}
			else
				f = 1;		//密码错误
		else
			f = 1;			//用户名错误
	}
	
	if (flag == 1&&f==1)
	{
		MessageBox(TEXT("用户名或密码错误"));
		return;
	}
}


void CDialogLogin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnClose();
	exit(0);
}


void CDialogLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}
