#if !defined(AFX_LOADEZDFILE_H__4ACDD9FE_6AF9_402D_9AA4_C933B3E75433__INCLUDED_)
#define AFX_LOADEZDFILE_H__4ACDD9FE_6AF9_402D_9AA4_C933B3E75433__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadEzdFile.h : header file
//
#include "MarkEzdDll.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CLoadEzdFile dialog
class CDemoView;
class CLoadEzdFile : public CDialog
{
// Construction
public:
	void OnDrawPreview();
	CLoadEzdFile(CWnd* pParent = NULL);   // standard constructor

	CBitmap* m_pPrevBmp;
	CDemoView* m_pCon;
	CMainFrame * m_pPFr;
	CString m_nReturnLoadFileName;
	BOOL m_nReadFlag;

	int m_nPenNo;
	int m_nMarkLoop;
	double m_ndMarkSpeed;
	double m_ndPowerRatio;
	double m_ndCurrent;
	
	int m_nFreq;
	int m_nQPluse;
	int m_nStartTC;
	int m_nLaserOffTC;
	int m_nEndTC;
	
	int m_nPolyTC;
	double m_ndJumpSpeed;
	int m_nJumpPosTC;
	int m_nJumpDisTC;
	double m_ndEndComp;
	
	double m_ndAccDist;
	double m_ndPointTime;
	BOOL m_nbPulsePointMode;
	int m_nPulseNum;
	double m_ndFlySpeed;
	

	
	

// Dialog Data
	//{{AFX_DATA(CLoadEzdFile)
	enum { IDD = IDD_LOADFILE };
		// NOTE: the ClassWizard will add data members here
	CString m_strFileName;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadEzdFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoadEzdFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilescan();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADEZDFILE_H__4ACDD9FE_6AF9_402D_9AA4_C933B3E75433__INCLUDED_)
