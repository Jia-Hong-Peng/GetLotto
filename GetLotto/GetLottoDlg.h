
// GetLottoDlg.h : 標頭檔
//

#pragma once
#include "SQLite.h"  
#pragma comment(lib,"sqlite.lib")   
using namespace SQLite;

// CGetLottoDlg 對話方塊
class CGetLottoDlg : public CDialogEx
{
// 建構
public:
	CGetLottoDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_GETLOTTO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
