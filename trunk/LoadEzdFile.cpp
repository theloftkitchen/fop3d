// LoadEzdFile.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "LoadEzdFile.h"
#include "demoView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadEzdFile dialog
extern CDemoApp theApp;

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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CLoadEzdFile::OnFilescan() 
{
	// TODO: Add your control notification handler code here
	
	CFileDialog dlg(TRUE,_T(""),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Ezcad file(*.ezd)|*.ezd|"));
	
	if(dlg.DoModal()==IDOK)
	{
		m_strFileName = dlg.GetPathName();
		UpdateData(FALSE);
		
		if(m_pCon->lmc1_LoadEzdFile==NULL )
		{
			return;
		}
		
		TCHAR szFile[256];
		_tcscpy(szFile,m_strFileName);
		int nErr = m_pCon->lmc1_LoadEzdFile(szFile);
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
    {//ÏÔÊ¾Ô¤ÀÀÍ¼Æ¬	
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
/*
	if (m_pCon != NULL)
	{
		delete m_pCon;
		m_pCon = NULL;
	}
	if (m_pPFr != NULL)
	{
		delete m_pPFr;
		m_pPFr = NULL;
	}*/

}



void CLoadEzdFile::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);

	CDialog::OnOK();
}
