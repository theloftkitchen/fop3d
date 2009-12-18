  // demoView.h : interface of the CDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#include "SelectDLG.h"
#include "ArcBall.h"
#include "MainFrm.h"

#include "MarkEzdDll.h"
#if !defined(AFX_DEMOVIEW_H__E69290EC_B14B_49E9_98BD_D705125C7B62__INCLUDED_)
#define AFX_DEMOVIEW_H__E69290EC_B14B_49E9_98BD_D705125C7B62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDemoDoc;
class CControlWnd;
//class CMainFrame;
class CDemoView : public CView
{
protected: // create from serialization only
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)


	





// Attributes
public:
	CDemoDoc* GetDocument();
	CMainFrame *m_pFr;
	CControlWnd *m_pControlWnd;


	void DrawAxis();
	SelectDLG dlgload;

	BOOL bSetupPixelFormat();
	void Init();
	void DrawScene(GLenum mode);
	void GlTexture();
	void DrawPoints(GLenum mode);
	void DrawTriMesh(GLenum mode);
	void ShowLight();
	void DrawIndex();

//   CControlWnd cntrldlg;

	int mouseX;
	int mouseY;
	float rot[3];
	float zoom;
	float xyshift[2];
	GLuint selectBuf[1000];
	GLuint selectindex;
	int deleteindex[5];
	float deletecontent[5][5];
	int nindeleteindex;
	BOOL LButtonSta;
	BOOL RButtonSta;
	BOOL TEXTURE;
	BOOL SHOWPOINTS;
	BOOL SHOWTRIMESH;
	BOOL ENABLELIGHT;
	BOOL ENABLEXYROTATE;
	BOOL ENABLEZROTATE;
	BOOL ENABLEXYSHIFT;
	BOOL ENABLEANIMATE;
	BOOL SHOWBACK;
	BOOL SHOWAXIS;
	BOOL SHOWINDEX;
	BOOL ENABLESELECT;
	BOOL CURSORINWND;
	BOOL CTRLKEYDOWN;
	UINT m_timer;
	
	
	GLfloat m_RotateAngle;
	GLfloat m_fRotateX;
	GLfloat m_fRotateY;
	GLfloat m_fRotateZ;
	


	
	
	//Arcball variables
	//	ArcBallT    ArcBall(640.0f, 480.0f);
	Point2fT    MousePt;// NEW: Current Mouse Point
	bool        isClicked;// NEW: Clicking The Mouse?
	bool        isRClicked;// NEW: Clicking The Right Mouse Button?
	bool        isDragging;// NEW: Dragging The Mouse?
	
	void CaculateNormal(GLdouble* dVertex1,GLdouble* dVertex2,
		GLdouble* dVertex3,GLdouble* dNormal);
	void DoSelect(CPoint point);
	void DeletePnt();

	//pointer of DLL function
	HINSTANCE m_hEzdDLL;
	LMC1_INITIAL lmc1_Initial;
	LMC1_CLOSE         lmc1_Close;
	LMC1_LOADEZDFILE   lmc1_LoadEzdFile;
	LMC1_MARKENTITY    lmc1_MarkEntity;
	LMC1_GETPREVBITMAP lmc1_GetPrevBitmap;
	LMC1_MARK lmc1_Mark;
	LMC1_READPORT  lmc1_ReadPort;
	LMC1_WRITEPORT lmc1_WritePort;
	
	LMC1_SETDEVCFG     lmc1_SetDevCfg; 
	LMC1_SETPENPARAM lmc1_SetPenParam;
	LMC1_GETPENPARAM lmc1_GetPenParam;
	LMC1_SAVEENTLIBTOFILE lmc1_SaveEntLibToFile;






// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CRect m_oldRect;
	CClientDC* m_pDC;
	//CMainFrame* pFrame;
	//CStatusBar* PStatus;
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	
	//{{AFX_MSG(CDemoView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLoad();
	afx_msg void OnShowPoints();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShowMesh();
	afx_msg void OnTextureMapping();
	afx_msg void OnXyshift();
	afx_msg void OnXyrotate();
	afx_msg void OnZrotate();
	afx_msg void OnResetcam();
	afx_msg void OnAnimate();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateShowPoints(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowMesh(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTextureMapping(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateXyrotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZrotate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateXyshift(CCmdUI* pCmdUI);
	afx_msg void OnShowback();
	afx_msg void OnUpdateShowback(CCmdUI* pCmdUI);
	afx_msg void OnShowindex();
	afx_msg void OnUpdateShowindex(CCmdUI* pCmdUI);
	afx_msg void OnLight();
	afx_msg void OnUpdateLight(CCmdUI* pCmdUI);
	afx_msg void OnEnableselect();
	afx_msg void OnUpdateEnableselect(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSaveresult();
	afx_msg void OnBackward();
	afx_msg void OnSavetrindex();
	afx_msg void OnShowaxis();
	afx_msg void OnUpdateShowaxis(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in demoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOVIEW_H__E69290EC_B14B_49E9_98BD_D705125C7B62__INCLUDED_)
