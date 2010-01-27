// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_nInfo = _T("");
	//}}AFX_DATA_INIT
	m_pConnection = NULL;
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_LOGININFO, m_nInfo);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->GetDlgItem(IDOK)->ShowWindow(FALSE);
	this->GetDlgItem(IDCANCEL)->ShowWindow(FALSE);
	
	this->ShowWindow(SW_SHOWNORMAL);
	HRESULT hr;
	try
	{
		this->m_nInfo = "正在进入系统,请稍候...";
			this->UpdateData(FALSE);
	
		Sleep(2000);
		hr = m_pConnection.CreateInstance(__uuidof(Connection));
		if (SUCCEEDED(hr))
		{
			m_pConnection->ConnectionString = "File Name=Data.udl";
			m_pConnection->ConnectionTimeout = 10;
			hr = m_pConnection->Open("","","",adConnectUnspecified);
			while (FAILED(hr))
			{
				hr = m_pConnection->Open("","","",adConnectUnspecified);
			}
			
			Sleep(1000);
			this->OnOK();

		} 
		else
		{
			MessageBox(_T("登陆失败!"),_T("错误"),0+16+0);
			SendMessage(WM_CLOSE,0,0);
		}
	}
	catch (_com_error e)
	{
		
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		AfxMessageBox(bstrSource+bstrDescription);
		exit(1);
		
	}
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
