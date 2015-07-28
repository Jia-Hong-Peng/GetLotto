
// GetLottoDlg.h : ���Y��
//

#pragma once
#include "SQLite.h"  
#pragma comment(lib,"sqlite.lib")   
using namespace SQLite;

// CGetLottoDlg ��ܤ��
class CGetLottoDlg : public CDialogEx
{
// �غc
public:
	CGetLottoDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_GETLOTTO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString strURL;
	CString strHTML;	

	

	afx_msg void OnBnClickedButtonGetSource();
	
	CString CGetLottoDlg::getParameters(int month, int year);
	CString CGetLottoDlg::getEVENTVALIDATION();
	CString CGetLottoDlg::getVIEWSTATE();
	CString CGetLottoDlg::GetInner(CString htmls, CString ff, CString ll);
	CString CGetLottoDlg::UrlEncode(CString url);

	CString EVENTVALIDATION;
	CString VIEWSTATE;
};
