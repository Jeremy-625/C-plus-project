
// C5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "C5.h"
#include "C5Dlg.h"
#include "afxdialogex.h"

#include "CDialogLogin.h"

#include <iostream>
#include <fstream>

#include "course.h"
#include "student.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int isg = 0;				//判断是否为研究生
int order = 0;				//学生序号
Student* tmp;				//登录学生
extern Course cou[12];		//课程信息
extern Ugstudent ugstu[30];	//本科生信息
extern Gstudent gstu[15];	//研究生信息
CDialogLogin login;			//登录窗口

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CC5Dlg 对话框



CC5Dlg::CC5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_C5_DIALOG, pParent)
	, m_name(_T(""))
	, m_id(_T(""))
	, m_type(_T(""))
	, m_credit(0)
	, m_tuition(0)
	, m_select(0)
	, m_quit(0)
	, m_numall(0)
	, m_teacher(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	//更改图标
}

void CC5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_id);
	DDX_Text(pDX, IDC_EDIT3, m_type);
	DDX_Text(pDX, IDC_EDIT4, m_credit);
	DDX_Text(pDX, IDC_EDIT5, m_tuition);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_LIST3, m_list2);
	DDX_Text(pDX, IDC_EDIT6, m_select);
	DDX_Text(pDX, IDC_EDIT7, m_quit);
	DDX_Text(pDX, IDC_EDIT8, m_numall);
	DDX_Text(pDX, IDC_EDIT9, m_teacher);
}

BEGIN_MESSAGE_MAP(CC5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CC5Dlg::OnLvnItemchangedList2)
	ON_EN_CHANGE(IDC_EDIT7, &CC5Dlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON6, &CC5Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CC5Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CC5Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CC5Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CC5Dlg 消息处理程序

BOOL CC5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	cou[0].initial();
	ugstu[0].initial();
	gstu[0].initial();				//初始化 

	login.DoModal();				//打开登录窗口
	if (isg)
		tmp = &gstu[order];
	else
		tmp = &ugstu[order];		//切换对象
	CString name(tmp->getname());
	m_name = name;					//获取学生姓名
	CString id(tmp->getid());
	m_id = id;						//获取学生学号
	if (isg)
	{
		m_type = TEXT("研究生");	//获取学生类别
	}
	else
	{
		m_type = TEXT("本科生");
	}	
	m_credit = tmp->getcredit();	//获取学生学分
	m_tuition = tmp->calculate();	//获取学生学费
	m_numall = cou->courseNumAll;	//获取总选课数
	CString teacher(tmp->getteachername());
	m_teacher = teacher;
	

	//更新列表1
	CString list[] = { TEXT("序号"),TEXT("类型"),TEXT("名称"),TEXT("学分"),TEXT("人数") };
	m_list.InsertColumn(0, list[0], LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, list[1], LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, list[2], LVCFMT_LEFT, 120);
	m_list.InsertColumn(3, list[3], LVCFMT_LEFT, 50);
	m_list.InsertColumn(4, list[4], LVCFMT_LEFT, 80);
	for (int i = 0; i < 12; i++)
	{
		CString index;
		index.Format(TEXT("%d"), cou[i].courseOrder);
		m_list.InsertItem(i, index);//序号

		CString type(cou[i].courseType);
		m_list.SetItemText(i, 1,type);//类型

		CString name(cou[i].courseName);
		m_list.SetItemText(i, 2, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), cou[i].courseCredit);
		m_list.SetItemText(i, 3, credit);//学分

		CString num;
		num.Format(TEXT("%d/%d"), cou[i].courseNum,15);
		m_list.SetItemText(i, 4, num);//人数

	}

	//更新列表2
	CString list2[] = { TEXT("课程序号"),TEXT("名称"),TEXT("学分") };
	m_list2.InsertColumn(0, list2[0], LVCFMT_LEFT, 80);
	m_list2.InsertColumn(1, list2[1], LVCFMT_LEFT, 110);
	m_list2.InsertColumn(2, list2[2], LVCFMT_LEFT, 50);
	for (int i = 0; i < tmp->studentSelect; i++)
	{
		CString index;
		index.Format(TEXT("%d"), tmp->studentCourse[i]->courseOrder);
		m_list2.InsertItem(i, index);//序号

		CString name(tmp->studentCourse[i]->courseName);
		m_list2.SetItemText(i, 1, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), tmp->studentCourse[i]->courseCredit);
		m_list2.SetItemText(i, 2, credit);//学分
	}

	UpdateData(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CC5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CC5Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CC5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CC5Dlg::OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CC5Dlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CC5Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CC5Dlg::OnBnClickedButton3()		//选课
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	for (int i = 0; i < tmp->studentSelect; i++)
		if (tmp->studentCourse[i]->courseOrder == m_select)
		{
			MessageBox(TEXT("重复选课"));
			return;
		}
	if (tmp->studentSelect == 5)
	{
		MessageBox(TEXT("选课数已达上限"));
		return;
	}
	if (cou[m_select - 1].courseNum == 15)
	{
		MessageBox(TEXT("该课程人数已满"));
		return;
	}
	tmp->studentCourse[tmp->studentSelect] = &cou[m_select-1];
	cou[m_select-1].addNum();
	tmp->studentSelect++;

	m_list2.DeleteAllItems();
	for (int i = 0; i < tmp->studentSelect; i++)
	{
		CString index;
		index.Format(TEXT("%d"), tmp->studentCourse[i]->courseOrder);
		m_list2.InsertItem(i, index);//序号

		CString name(tmp->studentCourse[i]->courseName);
		m_list2.SetItemText(i, 1, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), tmp->studentCourse[i]->courseCredit);
		m_list2.SetItemText(i, 2, credit);//学分
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < 12; i++)
	{
		CString index;
		index.Format(TEXT("%d"), cou[i].courseOrder);
		m_list.InsertItem(i, index);//序号

		CString type(cou[i].courseType);
		m_list.SetItemText(i, 1, type);//类型

		CString name(cou[i].courseName);
		m_list.SetItemText(i, 2, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), cou[i].courseCredit);
		m_list.SetItemText(i, 3, credit);//学分

		CString num;
		num.Format(TEXT("%d/%d"), cou[i].courseNum, 15);
		m_list.SetItemText(i, 4, num);//人数

	}
	m_credit = tmp->getcredit();
	m_tuition = tmp->calculate();
	m_numall = cou->courseNumAll;

	UpdateData(false);
}


void CC5Dlg::OnBnClickedButton4()//退课
{
	// TODO: 在此添加控件通知处理程序代码
	int flag = 1;
	UpdateData(true);
	for (int i = 0; i < tmp->studentSelect; i++)
		if (tmp->studentCourse[i]->courseOrder == m_quit)
		{
			flag = 0;
			break;
		}
	if (flag)
	{
		MessageBox(TEXT("退课错误"));
		return;
	}
	for(int i=0;i<tmp->studentSelect;i++)
		if (tmp->studentCourse[i]->courseOrder == m_quit)
		{
			int j = i + 1;
			for (j; j < tmp->studentSelect; j++)
				tmp->studentCourse[j - 1] = tmp->studentCourse[j];
			tmp->studentSelect--;
			cou[m_quit-1].subNum();
		}

	m_list2.DeleteAllItems();
	for (int i = 0; i < tmp->studentSelect; i++)
	{
		CString index;
		index.Format(TEXT("%d"), tmp->studentCourse[i]->courseOrder);
		m_list2.InsertItem(i, index);//序号

		CString name(tmp->studentCourse[i]->courseName);
		m_list2.SetItemText(i, 1, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), tmp->studentCourse[i]->courseCredit);
		m_list2.SetItemText(i, 2, credit);//学分
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < 12; i++)
	{
		CString index;
		index.Format(TEXT("%d"), cou[i].courseOrder);
		m_list.InsertItem(i, index);//序号

		CString type(cou[i].courseType);
		m_list.SetItemText(i, 1, type);//类型

		CString name(cou[i].courseName);
		m_list.SetItemText(i, 2, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), cou[i].courseCredit);
		m_list.SetItemText(i, 3, credit);//学分

		CString num;
		num.Format(TEXT("%d/%d"), cou[i].courseNum, 15);
		m_list.SetItemText(i, 4, num);//人数

	}
	m_credit = tmp->getcredit();
	m_tuition = tmp->calculate();
	m_numall = cou->courseNumAll;
	UpdateData(false);
}


void CC5Dlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CC5Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码

	login.DoModal();
	m_list.DeleteAllItems();
	m_list2.DeleteAllItems();

	if (isg)
		tmp = &gstu[order];
	else
		tmp = &ugstu[order];
	CString name(tmp->getname());
	m_name = name;
	CString id(tmp->getid());
	m_id = id;
	if (isg)
		m_type = TEXT("研究生");
	else
		m_type = TEXT("本科生");
	m_credit = tmp->getcredit();
	m_tuition = tmp->calculate();
	m_numall = cou->courseNumAll;
	CString teacher(tmp->getteachername());
	m_teacher = teacher;
	m_select = 0;
	m_quit = 0;

	for (int i = 0; i < 12; i++)
	{
		CString index;
		index.Format(TEXT("%d"), cou[i].courseOrder);
		m_list.InsertItem(i, index);//序号

		CString type(cou[i].courseType);
		m_list.SetItemText(i, 1, type);//类型

		CString name(cou[i].courseName);
		m_list.SetItemText(i, 2, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), cou[i].courseCredit);
		m_list.SetItemText(i, 3, credit);//学分

		CString num;
		num.Format(TEXT("%d/%d"), cou[i].courseNum, 15);
		m_list.SetItemText(i, 4, num);//人数

	}
	for (int i = 0; i < tmp->studentSelect; i++)
	{
		CString index;
		index.Format(TEXT("%d"), tmp->studentCourse[i]->courseOrder);
		m_list2.InsertItem(i, index);//序号

		CString name(tmp->studentCourse[i]->courseName);
		m_list2.SetItemText(i, 1, name);//名称

		CString credit;
		credit.Format(TEXT("%d"), tmp->studentCourse[i]->courseCredit);
		m_list2.SetItemText(i, 2, credit);//学分
	}

	UpdateData(false);
}
