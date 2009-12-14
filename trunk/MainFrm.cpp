 // MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "demo.h"

#include "MainFrm.h"
#include "ControlWnd.h"

#include "demoView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(MESSAGE_STEPPRO,ProgressStatus)



END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
 
	ID_PROGRESSTEXT,
	ID_PROGRESSSAREA,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_pTreeView = NULL;
	m_pCtrlWnd = NULL;
	m_bPCreat = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//指定面板的风格和宽度
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NOBORDERS,150);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	this->GetWndPointer();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	int cx =  GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	if(m_Splitter.CreateStatic(this,1,2)== NULL)
		return FALSE;
	if(!m_Splitter.CreateView(0,0,RUNTIME_CLASS(CDemoView),CSize(cx*2/3,cy),pContext))
	{
		m_Splitter.DestroyWindow();
		return FALSE;
	}
	if(!m_Splitter.CreateView(0,1,RUNTIME_CLASS(CControlWnd),CSize(cx/3,cy),pContext))
	{
		m_Splitter.DestroyWindow();
		return FALSE;
	}
	
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

void CMainFrame::GetWndPointer()
{
	CWnd *pWnd = NULL;
	pWnd = this->m_Splitter.GetPane(0,0);
	this->m_pTreeView = DYNAMIC_DOWNCAST(CDemoView,pWnd);
	pWnd = this->m_Splitter.GetPane(0,1);
	this->m_pCtrlWnd = DYNAMIC_DOWNCAST(CControlWnd,pWnd);


}

void CMainFrame::InvalidateAllWnd()
{
	this->m_pTreeView->Invalidate();


}

void CMainFrame::CreateProgress()
{
	RECT rect;
	m_wndStatusBar.GetItemRect(2,&rect);
	if (!m_bPCreat)
	{
		m_pProgress.Create(WS_VISIBLE|WS_CHILD|PBS_SMOOTH,rect,&m_wndStatusBar,10);
		m_pProgress.SetRange(0,100);
		m_pProgress.SetStep(1);
		m_bPCreat = TRUE;

	}


}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (m_bPCreat)
	{
		RECT rect;
		m_wndStatusBar.GetItemRect(2,&rect);
		m_pProgress.SetWindowPos(&wndTop,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_SHOWWINDOW);
	}
	
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::ProgressStatus(WPARAM wP, LPARAM lP)
{
	if (!m_bPCreat)
	{
		this->CreateProgress();
	}
	int n = wP;
	CString str;
	m_pProgress.SetPos(n);
	str.Format(_T("正在读取数据,请稍候...进度%d%%"),n);
	m_wndStatusBar.SetPaneText(/*m_wndStatusBar.CommandToIndex(ID_PROGRESSTEXT)*/1,str);
	if (100 == n)
	{
		m_pProgress.SetPos(0);
		if (this->m_pCtrlWnd->m_bRDflag)
		{
			m_wndStatusBar.SetPaneText(/*m_wndStatusBar.CommandToIndex(ID_PROGRESSTEXT)*/1,_T("数据成功获取!"));
			this->InvalidateAllWnd();
		}
		if (!this->m_pCtrlWnd->m_bRDflag)
		{
			m_wndStatusBar.SetPaneText(/*m_wndStatusBar.CommandToIndex(ID_PROGRESSTEXT)*/1,_T("数据获取失败"));
			this->InvalidateAllWnd();
		}
	}

		

}
