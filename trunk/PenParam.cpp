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
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenParam message handlers
