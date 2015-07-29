
// GetLottoDlg.h : 標頭檔
//

#pragma once
#include "SqlOperator.h"
#include "afxcmn.h"


struct NumberPeriod
{
	CString no;
	CString dateStart;
	CString dateClose;
	CString number1;
	CString number2;
	CString number3;
	CString number4;
	CString number5;
	CString number6;
	CString numberSP;
};

// CGetLottoDlg 對話方塊
class CGetLottoDlg : public CDialogEx
{
// 建構
public:
	SqlOperator Sql;
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
		

	

	afx_msg void OnBnClickedButtonGetSource();
	void CGetLottoDlg::InsertNum(NumberPeriod* myNumberPeriod);
	void CGetLottoDlg::getNumberPeriod(NumberPeriod* numPeriod, int month, int year);
	void CGetLottoDlg::SplitString(CStringArray& dst, const CString& src, LPCTSTR slipt);
	CString CGetLottoDlg::getParameters(int month, int year);
	CString CGetLottoDlg::getEVENTVALIDATION(CString strHTML);
	CString CGetLottoDlg::getVIEWSTATE(CString strHTML);
	CString CGetLottoDlg::GetInner(CString htmls, CString ff, CString ll);
	

	CString CGetLottoDlg::getNumberMain(CString output);
	CString CGetLottoDlg::getNumberSP(CString output);
	CString CGetLottoDlg::getNumber6(CString output);
	CString CGetLottoDlg::getNumber5(CString output);
	CString CGetLottoDlg::getNumber4(CString output);
	CString CGetLottoDlg::getNumber3(CString output);
	CString CGetLottoDlg::getNumber2(CString output);
	CString CGetLottoDlg::getNumber1(CString output);
	CString CGetLottoDlg::getClose(CString output);
	CString CGetLottoDlg::getStart(CString output);
	CString CGetLottoDlg::getNo(CString output);
	CString EVENTVALIDATION;
	CString VIEWSTATE;
	virtual BOOL DestroyWindow();
	CProgressCtrl m_myProgress;
};
