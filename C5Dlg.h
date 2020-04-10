
// C5Dlg.h: 头文件
//

#pragma once


// CC5Dlg 对话框
class CC5Dlg : public CDialogEx
{
// 构造
public:
	CC5Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_C5_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_id;
	CString m_type;
	int m_credit;
	int m_tuition;
	afx_msg void OnLvnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_list;
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnBnClickedButton6();
	CListCtrl m_list2;
	int m_select;
	int m_quit;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	virtual void OnOK();
	int m_numall;
	afx_msg void OnBnClickedButton5();
	CString m_teacher;
};
