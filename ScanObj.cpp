// ScanObj.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ScanObj.h"
#include "demoView.h"
#include "ni488.h"
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
	m_nDistance = .0f;
	m_nResolution = .0f;
	m_nReturnDistance = 1000.0f;

	//}}AFX_DATA_INIT
}


void CScanObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanObj)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX,IDC_EDIT_DISTANCE,m_nDistance);
	DDX_Text(pDX,IDC_EDIT_RESOLUTION,m_nResolution);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanObj, CDialog)
	//{{AFX_MSG_MAP(CScanObj)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_SCANSTART, OnScanstart)
	ON_BN_CLICKED(IDC_COUNTDISTANCE, OnCountdistance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanObj message handlers

BOOL CScanObj::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pFr = (CMainFrame*)AfxGetMainWnd();
	m_pDemoView = m_pFr->m_pTreeView;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScanObj::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CScanObj::OnScanstart() 
{
	// TODO: Add your control notification handler code here
	
	WORD startGreen=0xc000;//打开激光，绿光
	WORD closeGreen=0x0000;
    CString off=_T("瞄准(OFF)"),on=_T("瞄准(ON)"),tmp;
	
	if (GetDlgItemText(IDC_SCANSTART,tmp)&&tmp==off)
	{
		SetDlgItemText(IDC_SCANSTART,on);
		try
		{
			this->m_pDemoView->lmc1_WritePort(startGreen);
		}
		catch (CMemoryException* e)
		{
			return;
		}
		catch (CFileException* e)
		{
			return;
			
		}
		catch (CException* e)
		{
			AfxMessageBox(_T("lmc1_WritePort  ERROR!"));
			return;
		}
	}
	else
	{
		SetDlgItemText(IDC_SCANSTART,off);
		try
		{
			m_pDemoView->lmc1_WritePort(closeGreen);
		}
		catch (CMemoryException* e)
		{
			return;
		}
		catch (CFileException* e)
		{
			return;
			
		}
		catch (CException* e)
		{
			AfxMessageBox(_T("lmc1_WritePort  ERROR!"));
			return;
		}
	}
}

void CScanObj::OnCountdistance() 
{
	// TODO: Add your control notification handler code here
	char buffer[101];
	int Device;
	double data;
	int   PrimaryAddress = 1;      /* Primary address of the device           */
	int   SecondaryAddress = 0;    /* Secondary address of the device         */
	int	  BoardIndex=0;
	
	
	
	/*****************************************************************************
	* Initialization - Done only once at the beginning of your application.
	*****************************************************************************/
	
	Device = ibdev(                /* Create a unit descriptor handle         */
		BoardIndex,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		PrimaryAddress,          /* Device primary address                  */
		SecondaryAddress,        /* Device secondary address                */
		T30s,                    /* Timeout setting (T10s = 10 seconds)     */
		1,                       /* Assert EOI line at end of write         */
		0);                      /* EOS termination mode                    */
	if (ibsta & ERR) {             /* Check for GPIB Error                    */
	//	GpibError("ibdev Error"); 
	}
	
	
	
	
	ibclr(Device);                 /* Clear the device                        */
/*
	if (ibsta & ERR) {
		GpibError("ibclr Error");
	}
	*/

	
	
	ibwrt(Device,"*RST;MODE 0;SRCE 0;ARMM 1;SIZE 1",32);
	/*
	if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}*/
	
	ibwrt(Device,"STRT;*WAI;XAVG?",15);
	/*
	if (ibsta & ERR) {
			GpibError("ibwrt Error");
		}*/
	
	m_pDemoView->lmc1_WritePort(0x8000);
	
	ibrd(Device,buffer,100);
/*
	if (ibsta & ERR) {
		GpibError("ibrd Error");
	}*/

	buffer[ibcntl]='\n';
	//	CString tmp;
	//	sprintf(tmp,"%s",buffer);
	data=atof(buffer);
	
	long  CV=299792458;
	m_nDistance = CV*(data)/2;
	m_nReturnDistance = m_nDistance;
	m_nResolution=m_nDistance*10*3.1415926/(180*160.0);
	
	UpdateData(FALSE);
}

void CScanObj::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_nDistance = .0f;
	m_nResolution = .0f;
	//m_nReturnDistance = 1000.0f;

	CDialog::OnOK();
}

void CScanObj::OnCancel() 
{
	// TODO: Add extra cleanup here
//	AfxMessageBox(_T("没有指定扫描距离基准值!,默认值为1000"));
	m_nDistance = .0f;
	m_nResolution = .0f;
	m_nReturnDistance = 1000.0f;


//	SendMessage(WM_CLOSE,0,0);


	CDialog::OnCancel();
}
