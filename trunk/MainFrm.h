// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__17B4AA10_3E5C_4FE0_A37A_D5EDA060B8D7__INCLUDED_)
#define AFX_MAINFRM_H__17B4AA10_3E5C_4FE0_A37A_D5EDA060B8D7__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CControlWnd;
class CDemoView;
class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

	

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
//	void ProgressStatus(WPARAM wP,LPARAM lP);
	void CreateProgress();
	void InvalidateAllWnd();
	void GetWndPointer();

	CControlWnd *m_pCtrlWnd;
	CDemoView *m_pTreeView;
	CSplitterWnd m_Splitter;
	CProgressCtrl m_pProgress;
	BOOL m_bPCreat;

	

	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	//CStatusBar  m_wndStatusBar;
	//CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	afx_msg void ProgressStatus(WPARAM wP,LPARAM lP);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17B4AA10_3E5C_4FE0_A37A_D5EDA060B8D7__INCLUDED_)
