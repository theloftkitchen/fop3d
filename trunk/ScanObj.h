#if !defined(AFX_SCANOBJ_H__96FD8EC5_AEDD_4E45_B954_4A58DD48F74E__INCLUDED_)
#define AFX_SCANOBJ_H__96FD8EC5_AEDD_4E45_B954_4A58DD48F74E__INCLUDED_

#include "MainFrm.h"	// Added by ClassView
//#include "AxisTransform.h"
//#include "demoView.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanObj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanObj dialog
class CDemoView;
class CScanObj : public CDialog
{
// Construction
public:
	double m_resolution;
	CDemoView *m_pDemoView;
	CMainFrame *m_pFr;
	CScanObj(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanObj)
	enum { IDD = IDD_SCANOBJ };
	double	m_distance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanObj)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanObj)
	afx_msg void OnScanstart();
	virtual BOOL OnInitDialog();
	afx_msg void OnCountdistance();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANOBJ_H__96FD8EC5_AEDD_4E45_B954_4A58DD48F74E__INCLUDED_)
