
// GetLottoDlg.cpp : ��@��
//

#include "stdafx.h"
#include "GetLotto.h"
#include "GetLottoDlg.h"
#include "afxdialogex.h"

#include "HttpClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HttpClient m_httpClient;


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	// �{���X��@
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


// CGetLottoDlg ��ܤ��



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


// CGetLottoDlg �T���B�z�`��

BOOL CGetLottoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
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

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO:  �b���[�J�B�~����l�]�w
	Sql.OpenDb(_T("GetLotto.db"));
	Sql.Execute(_T("CREATE TABLE big_lotto([no] VARCHAR(255) PRIMARY KEY,[opendate] VARCHAR(255),[closedate] VARCHAR(255),[number] VARCHAR(255),[number_1] VARCHAR(255),[number_2] VARCHAR(255),[number_3] VARCHAR(255),[number_4] VARCHAR(255),[number_5] VARCHAR(255),[number_6] VARCHAR(255),[number_sp] VARCHAR(255));"));

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CGetLottoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CGetLottoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetLottoDlg::OnBnClickedButtonGetSource()
{
	NumberPeriod numberPeriod[20];

	

	CTime currTime = CTime::GetCurrentTime();
	int iYear = (int)currTime.GetYear();
	int iYearTw = iYear - 1911;

	for (int yy = 103; yy <= iYearTw; yy++)
	{
		for (int mm = 1; mm <= 12; mm++)
		{
			getNumberPeriod(numberPeriod, mm, yy);
			InsertNum(numberPeriod);
		}
	}

	UpdateData(FALSE);

}


void CGetLottoDlg::InsertNum(NumberPeriod* n)
{
	//bool result = false;

	CString sql = L"insert into big_lotto( [no],[opendate],[closedate],[number],[number_1],[number_2],[number_3],[number_4],[number_5],[number_6],[number_sp]) values('@no','@opendate', '@closedate', '@number_all', '@number_1', '@number_2', '@number_3', '@number_4' , '@number_5', '@number_6', '@number_sp') ";
	for (int i = 0; i < 20; i++)
	{
		if (!n[i].no.IsEmpty())
		{
			Table tb = Sql.Select(L"big_lotto", L"*", L"where no = '" + n[i].no + L"' ");
			BOOL isExist = (tb.GetRowCount() > 0) ? TRUE : FALSE;
			if (!isExist)
			{

				CString sql_tmp = sql;

				sql_tmp.Replace(L"@no", n[i].no);
				sql_tmp.Replace(L"@opendate", n[i].dateStart);
				sql_tmp.Replace(L"@closedate", n[i].dateClose);
				sql_tmp.Replace(L"@number_all", n[i].number1 + n[i].number2 + n[i].number3 + n[i].number4 + n[i].number5 + n[i].number6 + n[i].numberSP);
				sql_tmp.Replace(L"@number_1", n[i].number1);
				sql_tmp.Replace(L"@number_2", n[i].number2);
				sql_tmp.Replace(L"@number_3", n[i].number3);
				sql_tmp.Replace(L"@number_4", n[i].number4);
				sql_tmp.Replace(L"@number_5", n[i].number5);
				sql_tmp.Replace(L"@number_6", n[i].number6);
				sql_tmp.Replace(L"@number_sp", n[i].numberSP);

				Sql.Execute(sql_tmp);
				//result = true;

			}
		}
	}


	//return result;
}


void CGetLottoDlg::getNumberPeriod(NumberPeriod* numberPeriod, int month, int year)
{


	CString  myParameters = getParameters(month, year);

	CString strMyHTML = m_httpClient.HTTPPost(strURL, myParameters, TRUE, NULL, &m_httpClient.g_cookie);

	CString strMainHTML = getNumberMain(strMyHTML);

	CStringArray words ;
	LPCTSTR slipt = L"���O";
	SplitString(words, strMainHTML, slipt);

	if (words.GetSize() > 2)
	{


		for (int i = 1; i < words.GetSize(); i++) //��0�ӬO�U���T��
		{
			CString strWord = words[i];
			numberPeriod[words.GetSize() - (i - 1)].no = getNo(strWord);
			numberPeriod[words.GetSize() - (i - 1)].dateStart = getStart(strWord);
			numberPeriod[words.GetSize() - (i - 1)].dateClose = getClose(strWord);
			numberPeriod[words.GetSize() - (i - 1)].number1 = getNumber1(strWord);
			numberPeriod[words.GetSize() - (i - 1)].number2 = getNumber2(strWord);
			numberPeriod[words.GetSize() - (i - 1)].number3 = getNumber3(strWord);
			numberPeriod[words.GetSize() - (i - 1)].number4 = getNumber4(strWord);
			numberPeriod[words.GetSize() - (i - 1)].number5 = getNumber5(strWord);
			numberPeriod[words.GetSize() - (i - 1)].number6 = getNumber6(strWord);
			numberPeriod[words.GetSize() - (i - 1)].numberSP = getNumberSP(strWord);
		}
	}
}



void CGetLottoDlg::SplitString(CStringArray& dst, const CString& src, LPCTSTR slipt)
{
	dst.RemoveAll();
	const int len = _tcslen(slipt);

	int start = 0, end = 0;
	while ((end = src.Find(slipt, end)) != -1)
	{
		dst.Add(src.Mid(start, end - start));
		start = end += len;
	}
	dst.Add(src.Right(src.GetLength() - start));
}


CString CGetLottoDlg::getParameters(int month, int year)
{

	strHTML = m_httpClient.HTTPGet(strURL, TRUE, NULL, &m_httpClient.g_cookie);
	EVENTVALIDATION = getEVENTVALIDATION();
	VIEWSTATE = getVIEWSTATE();

	CString strMonth;
	strMonth.Format(L"%d", month);

	CString strYear;
	strYear.Format(L"%d", year);

	CString str1 = L"__EVENTTARGET=&__EVENTARGUMENT=&__LASTFOCUS=&__VIEWSTATE=" + m_httpClient.EncodeURI(VIEWSTATE);
	CString str2 = L"&__EVENTVALIDATION=" + m_httpClient.EncodeURI(EVENTVALIDATION);
	CString str3 = L"&Lotto649Control_history%24DropDownList1=2&Lotto649Control_history%24chk=radYM&Lotto649Control_history%24dropYear=" + strYear;
	CString str4 = L"&Lotto649Control_history%24dropMonth=" + strMonth;
	CString str5 = L"&Lotto649Control_history%24btnSubmit=%E6%9F%A5%E8%A9%A2";

	return str1 + str2 + str3 + str4 + str5;

}


CString CGetLottoDlg::getEVENTVALIDATION()
{
	CString strOutput = strHTML;

	strOutput = GetInner(strOutput, L"__EVENTVALIDATION", L"<div id=\"wrapper\">");
	strOutput = GetInner(strOutput, L"value=\"", L"\" />");
	strOutput.Replace(L"value=\"", L"");

	return strOutput;
}

CString CGetLottoDlg::getVIEWSTATE()
{
	CString strOutput = strHTML;

	strOutput = GetInner(strOutput, L"__VIEWSTATE", L"__EVENTVALIDATION");
	strOutput = GetInner(strOutput, L"value=\"", L"\" />");
	strOutput.Replace(L"value=\"", L"");

	return strOutput;
}



CString CGetLottoDlg::getNumberSP(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_No7_", L"�j�p����");
	strOutput = GetInner(strOutput, L"\">", L"</span></span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}
CString CGetLottoDlg::getNumber6(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_SNo6_", L"Lotto649Control_history_dlQuery_No7_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}
CString CGetLottoDlg::getNumber5(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_SNo5_", L"Lotto649Control_history_dlQuery_SNo6_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getNumber4(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_SNo4_", L"Lotto649Control_history_dlQuery_SNo5_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getNumber3(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_SNo3_", L"Lotto649Control_history_dlQuery_SNo4_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getNumber2(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_SNo2_", L"Lotto649Control_history_dlQuery_SNo3_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getNumber1(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_SNo1_", L"Lotto649Control_history_dlQuery_SNo2_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getClose(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_L649_EDate_", L"Lotto649Control_history_dlQuery_L649_SellAmount_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getStart(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_L649_DDate_", L"Lotto649Control_history_dlQuery_L649_EDate_");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getNo(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"Lotto649Control_history_dlQuery_L649_DrawTerm_", L"Lotto649Control_history1_dlQuery_ctl00_L649_DDate");
	strOutput = GetInner(strOutput, L"\">", L"</span>");
	strOutput.Replace(L"\">", L"");
	return strOutput;
}

CString CGetLottoDlg::getNumberMain(CString output)
{
	CString strOutput = output;
	strOutput = GetInner(strOutput, L"�몺�������X", L"���G");
	strOutput = GetInner(strOutput, L"�j�ֳz", L"<div class=\"intx01\">");
	strOutput.Replace(L"\r\n", L"");
	strOutput.Replace(L"  ", L"");
	strOutput.Replace(L"&nbsp;", L"");
	return strOutput;
}

CString CGetLottoDlg::GetInner(CString htmls, CString ff, CString ll)
{
	int first = htmls.Find(ff);
	int last = htmls.Find(ll);
	CString output = htmls.Mid(first, last - first);
	return output;
}







BOOL CGetLottoDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	Sql.CloseDb();
	return CDialogEx::DestroyWindow();
}
