// ScanObj.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ScanObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanObj dialog


CScanObj::CScanObj(CWnd* pParent /*=NULL*/)
	: CDialog(CScanObj::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanObj)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CScanObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanObj)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanObj, CDialog)
	//{{AFX_MSG_MAP(CScanObj)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanObj message handlers
