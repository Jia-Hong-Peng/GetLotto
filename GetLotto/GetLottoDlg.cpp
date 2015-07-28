
// GetLottoDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "GetLotto.h"
#include "GetLottoDlg.h"
#include "afxdialogex.h"

#include "HttpClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGetLottoDlg 對話方塊



CGetLottoDlg::CGetLottoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetLottoDlg::IDD, pParent)
	, strURL(_T("http://www.taiwanlottery.com.tw/Lotto/Lotto649/history.aspx"))
	, strHTML(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetLottoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_URL, strURL);
	DDX_Text(pDX, IDC_EDIT_HTML, strHTML);
}

BEGIN_MESSAGE_MAP(CGetLottoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON_GET_SOURCE, &CGetLottoDlg::OnBnClickedButtonGetSource)
END_MESSAGE_MAP()


// CGetLottoDlg 訊息處理常式

BOOL CGetLottoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CGetLottoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CGetLottoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CGetLottoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetLottoDlg::OnBnClickedButtonGetSource()
{
	
	
	EVENTVALIDATION = getEVENTVALIDATION();
	VIEWSTATE = getVIEWSTATE();

	CString  myParameters = getParameters( 1, 104);

	

	HttpClient m_httpClient;
	//strHTML = m_httpClient.HTTPGet(strURL, TRUE, NULL, &m_httpClient.g_cookie);
	
	strHTML = m_httpClient.HTTPPost(strURL, myParameters, TRUE, NULL, &m_httpClient.g_cookie);

	UpdateData(FALSE);
}


CString CGetLottoDlg::getParameters(int month, int year)
{
	CString strMonth;
	strMonth.Format(L"%d", month);

	CString strYear;
	strYear.Format(L"%d", year);

	CString type = L"Lotto649Control_history%24DropDownList1=2";
	CString btn = L"&Lotto649Control_history%24btnSubmit=%E6%9F%A5%E8%A9%A2";
	CString radYM = L"&Lotto649Control_history%24chk=radYM";
	CString mmm = L"&Lotto649Control_history%24dropMonth=" + strMonth;
	CString yyy = L"&Lotto649Control_history%24dropYear=" + strYear;
	CString other = L"&__EVENTARGUMENT=&__EVENTTARGET=";
	CString key1 = L"&__EVENTVALIDATION=" + UrlEncode(EVENTVALIDATION);
	CString key2 = L"&__LASTFOCUS=&__VIEWSTATE=" + UrlEncode(VIEWSTATE);
	//CString end = L"&__VIEWSTATEENCRYPTED=";

	return type + btn + radYM + mmm + yyy + other + key1 + key2;// +end;

}


CString CGetLottoDlg::getEVENTVALIDATION()
{
	CString output = strHTML;
	
	output = GetInner(output, L"__EVENTVALIDATION", L"<div id=\"wrapper\">");
	output = GetInner(output, L"value=\"", L"\" />");
	output.Replace(L"value=\"", L"");

	return output;
}

CString CGetLottoDlg::getVIEWSTATE()
{
	CString output = strHTML;
	
	output = GetInner(output, L"__VIEWSTATE", L"__EVENTVALIDATION");
	output = GetInner(output, L"value=\"", L"\" />");
	output.Replace(L"value=\"", L"");

	return output;
}


CString CGetLottoDlg::GetInner(CString htmls, CString ff, CString ll)
{
	int first = htmls.Find(ff);
	int last = htmls.Find(ll); 
	CString output = htmls.Mid(first, last - first);
	return output;
}



CString CGetLottoDlg::UrlEncode(CString url)
{
	url.Replace(_T("%"), _T("%25"));
	url.Replace(_T("!"), _T("%21"));
	url.Replace(_T("*"), _T("%2A"));
	url.Replace(_T("'"), _T("%27"));
	url.Replace(_T("("), _T("%28"));
	url.Replace(_T(")"), _T("%29"));
	url.Replace(_T(";"), _T("%3B"));
	url.Replace(_T(":"), _T("%3A"));
	url.Replace(_T("@"), _T("%40"));
	url.Replace(_T("&"), _T("%26"));
	url.Replace(_T("="), _T("%3D"));
	url.Replace(_T("+"), _T("%2B"));
	url.Replace(_T("$"), _T("%24"));
	url.Replace(_T(","), _T("%2C"));
	url.Replace(_T("/"), _T("%2F"));
	url.Replace(_T("?"), _T("%3F"));
	url.Replace(_T("#"), _T("%23"));
	url.Replace(_T("["), _T("%5B"));
	url.Replace(_T("]"), _T("%5D"));
	url.Replace(_T(" "), _T("%20"));
	url.Replace(_T("\r\n"), _T("%2C"));
	url.Replace(_T("\n"), _T("%2C"));
	url.Replace(_T("\""), _T("%22"));

	return url;
}


