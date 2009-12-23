// LoadEzdFile.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "LoadEzdFile.h"
#include "demoView.h"
#include "demoDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadEzdFile dialog
extern CDemoApp theApp;
BOOL m_IsLoad;


CLoadEzdFile::CLoadEzdFile(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadEzdFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadEzdFile)
		// NOTE: the ClassWizard will add member initialization here
	m_strFileName = _T("");

	//}}AFX_DATA_INIT
	m_pPrevBmp = NULL;
//	m_pContrlWnd = NULL;
	m_pCon = NULL;
	m_pPFr = NULL;
	m_IsLoad = FALSE;
	m_nReturnLoadFileName = _T("");
	m_nReadFlag = FALSE;

	m_nbPulsePointMode = FALSE;
	m_ndAccDist = 0;
	m_ndCurrent = 0;
	m_ndEndComp = 0;
	m_ndFlySpeed =0;
	m_ndJumpSpeed = 0;
	m_ndMarkSpeed = 0;
	m_ndPointTime = 0;
	m_ndPowerRatio = 0;
	m_nEndTC = 0;
	m_nFreq = 0;
	m_nJumpDisTC = 0;
	m_nJumpPosTC = 0;
	m_nLaserOffTC = 0;
	m_nMarkLoop = 0;
	m_nPenNo = 0;
	m_nPolyTC = 0;
	m_nPulseNum = 0;
	m_nQPluse = 0;
	m_nStartTC = 0;

}


void CLoadEzdFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadEzdFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Text(pDX,IDC_EZDFILENAME,m_strFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadEzdFile, CDialog)
	//{{AFX_MSG_MAP(CLoadEzdFile)
	ON_BN_CLICKED(IDC_FILESCAN, OnFilescan)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadEzdFile message handlers

BOOL CLoadEzdFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_pContrlWnd = (CMainFrame*)AfxGetApp()->m_pMainWnd->m_pCtrlWnd;
	m_pPFr = (CMainFrame*)AfxGetMainWnd();
	m_pCon = m_pPFr->m_pTreeView;
	this->GetDlgItem(IDC_FILESCAN)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CLoadEzdFile::OnFilescan() 
{
	// TODO: Add your control notification handler code here
		CDemoDoc *pDoc = m_pCon->GetDocument();
	
	CFileDialog dlg(TRUE,_T(""),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Ezcad file(*.ezd)|*.ezd|"));
	
	if(dlg.DoModal()==IDOK)
	{
		m_strFileName = dlg.GetPathName();
		m_nReturnLoadFileName = m_strFileName;
		m_nReadFlag = TRUE;
		m_IsLoad = TRUE;

		UpdateData(FALSE);
		
		if(m_pCon->lmc1_LoadEzdFile==NULL )
		{
			return;
		}
		
		TCHAR szFile[256];
		_tcscpy(szFile,m_strFileName);
		int nErr = m_pCon->lmc1_LoadEzdFile(szFile);
	//get the value;

		m_pCon->lmc1_GetPenParam(m_nPenNo,m_nMarkLoop,m_ndMarkSpeed,m_ndPowerRatio,m_ndCurrent,
			m_nFreq,m_nQPluse,m_nStartTC,m_nLaserOffTC,m_nEndTC,
			m_nPolyTC,m_ndJumpSpeed,m_nJumpPosTC,m_nJumpDisTC,m_ndEndComp,
			m_ndAccDist,m_ndPointTime,m_nbPulsePointMode,m_nPulseNum,m_ndFlySpeed
			
									);
		pDoc->m_nPenNo = m_nPenNo;
		pDoc->m_nMarkLoop = m_nMarkLoop;
		pDoc->m_ndMarkSpeed = m_ndMarkSpeed;
		pDoc->m_ndPowerRatio = m_ndPowerRatio;
		pDoc->m_ndCurrent = m_ndCurrent;
		pDoc->m_nFreq = m_nFreq;
		pDoc->m_nQPluse = m_nQPluse;
		pDoc->m_nStartTC = m_nStartTC;
		pDoc->m_nLaserOffTC = m_nLaserOffTC;
		pDoc->m_nEndTC = m_nEndTC;
		pDoc->m_nPolyTC = m_nPolyTC;
		pDoc->m_ndJumpSpeed = m_ndJumpSpeed;
		pDoc->m_nJumpDisTC = m_nJumpDisTC;
		pDoc->m_nJumpPosTC = m_nJumpPosTC;
		pDoc->m_ndEndComp = m_ndEndComp;
		pDoc->m_ndAccDist = m_ndAccDist;
		pDoc->m_ndPointTime = m_ndPointTime;
		pDoc->m_nbPulsePointMode = m_nbPulsePointMode;
		pDoc->m_nPulseNum = m_nPulseNum;
		pDoc->m_ndFlySpeed = m_ndFlySpeed;

		
		//end getting the value;



		if(nErr!=LMC1_ERR_SUCCESS)
		{
			AfxMessageBox(_T("Read ezdfile failed!"));				
		}
		
		if(m_pCon->lmc1_GetPrevBitmap==NULL)
		{
			return;
		}
		
		if(m_pPrevBmp!=NULL)
		{
			delete m_pPrevBmp;
			m_pPrevBmp = NULL;
		}
		
		CWnd* pWnd = GetDlgItem(IDC_STATIC_WND);
		if(pWnd==NULL)
			return;    	
		
		CRect rect;
		pWnd->GetClientRect(rect);
		
		CClientDC previewDC(pWnd);
		int nCaps = previewDC.GetDeviceCaps(BITSPIXEL);
		CDC* pDC = &previewDC;
		
		m_pPrevBmp = m_pCon->lmc1_GetPrevBitmap(pWnd->GetSafeHwnd(),rect.Width(),rect.Height());
		OnDrawPreview();
	}
	else
	{
			MessageBox(_T("没有打开任何文件!"),_T("提示"),0+48+0);
		
	}
}

void CLoadEzdFile::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	OnDrawPreview();
	// Do not call CDialog::OnPaint() for painting messages
}



void CLoadEzdFile::OnDrawPreview()
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_WND);
	if(pWnd==NULL)
		return;    	
	//	pWnd = this;
	CRect rect;
    pWnd->GetClientRect(rect);
    rect.InflateRect(-2,-2);
    
	CDC* pDC = pWnd->GetDC(); 
	CRgn pRgn;
	pRgn.CreateRectRgnIndirect(rect);
	pDC->SelectClipRgn(&pRgn);
	
	//CBrush Brsh(GetSysColor(COLOR_BTNFACE));
	CBrush Brsh(RGB(255,255,255));
	pDC->FillRect(rect,&Brsh);	
	if(m_pPrevBmp != NULL)
    {//显示预览图片	
		CDC memDC;
		CBitmap* pOld=NULL;
		memDC.CreateCompatibleDC(pDC);
		
		pOld = memDC.SelectObject(m_pPrevBmp);
		
		BITMAP bm;
		m_pPrevBmp->GetBitmap(&bm);		
		CPoint ptCen = rect.CenterPoint ();
		::SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);	
		
		pDC->BitBlt (ptCen.x - bm.bmWidth/2,ptCen.y - bm.bmHeight/2,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
		
		memDC.SelectObject(pOld);		
	}	
	
	pWnd->ReleaseDC( pDC );     
    return;

}

void CLoadEzdFile::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pPrevBmp != NULL)
	{
		delete m_pPrevBmp;
		m_pPrevBmp = NULL;
	}


}



void CLoadEzdFile::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);


	GetDlgItem(IDC_EZDFILENAME)->SetWindowText(_T(""));
	GetDlgItem(IDC_EZDFILENAME)->SetFocus();


	CDialog::OnOK();
}

void CLoadEzdFile::OnCancel() 
{
	// TODO: Add extra cleanup here
	SendMessage(WM_CLOSE,0,0);

	CDialog::OnCancel();
}
