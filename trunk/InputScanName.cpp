// InputScanName.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "InputScanName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputScanName dialog

extern CDemoApp theApp;

CInputScanName::CInputScanName(CWnd* pParent /*=NULL*/)
	: CDialog(CInputScanName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputScanName)
		// NOTE: the ClassWizard will add member initialization here
	m_nScanObjectName = _T("");
	m_nReturnName = _T("");

//	m_nScanNumQuery = 160.0;
	//}}AFX_DATA_INIT
	m_pRecord = NULL;

}


void CInputScanName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputScanName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX,IDC_INPUTSCANNAME,m_nScanObjectName);
	DDV_MaxChars(pDX,m_nScanObjectName,10);
//	DDX_Text(pDX,IDC_SCANNUMQUERY,m_nScanNumQuery);
//	DDV_MinMaxDouble(pDX,m_nScanNumQuery,160.0,256.0);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputScanName, CDialog)
	//{{AFX_MSG_MAP(CInputScanName)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputScanName message handlers

void CInputScanName::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_pRecord.CreateInstance(__uuidof(Recordset));
	CString vSQLIN;
	CString strFor;
	strFor.Format(_T("select distinct DATANAME from datatable where DATANAME = '%s'"),m_nScanObjectName);
	m_pRecord = theApp.m_pConnection->Execute(_bstr_t(strFor),NULL,adCmdText);
	if((m_pRecord->BOF) && (m_pRecord->adoEOF))
	{
		m_nReturnName = m_nScanObjectName;
		m_nScanObjectName = _T("");
		UpdateData(FALSE);


		CDialog::OnOK();
		
	}
	else
	{
		if (MessageBox(_T("请重新输入一个名字!"),_T("提示"),4+48+0)==IDYES)
		{
			m_nScanObjectName = _T("");
			this->GetDlgItem(IDC_INPUTSCANNAME)->SetFocus();
			this->UpdateData(FALSE);
			
		}
		
		
		
	}
	


//	UpdateData(FALSE);

    	

	
}

void CInputScanName::OnCancel() 
{
	// TODO: Add extra cleanup here
//	UpdateData(FALSE);
//	SendMessage(WM_CLOSE,0,0);
	m_nScanObjectName = _T("");
	UpdateData(FALSE);



	CDialog::OnCancel();
}

BOOL CInputScanName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->GetDlgItem(IDC_STATICSCAN)->ShowWindow(FALSE);
	this->GetDlgItem(IDC_SCANNUMQUERY)->ShowWindow(false);
	this->GetDlgItem(IDC_INPUTSCANNAME)->SetFocus();





	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




void CInputScanName::OnDestroy() 
{
	CDialog::OnDestroy();
	
	/*
	if (m_pRecord->State)
			{
				m_pRecord->Close();
				m_pRecord = NULL;
			}
		*/
	

	
}




