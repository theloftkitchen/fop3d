// PenParam.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "PenParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPenParam dialog
extern BOOL m_nIsLoad;

CPenParam::CPenParam(CWnd* pParent /*=NULL*/)
	: CDialog(CPenParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPenParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPenParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPenParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPenParam, CDialog)
	//{{AFX_MSG_MAP(CPenParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenParam message handlers

BOOL CPenParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_nIsLoad == FALSE)
	{
		AfxMessageBox(_T("请先载入模型文件!"));
		exit(1);
			
	}
	//initial variable


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPenParam::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_nIsLoad = FALSE;

	CDialog::OnOK();
}
