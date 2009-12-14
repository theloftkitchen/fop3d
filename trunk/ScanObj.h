#if !defined(AFX_SCANOBJ_H__F84946D0_D8E8_4393_BDE2_4B01B5379EA1__INCLUDED_)
#define AFX_SCANOBJ_H__F84946D0_D8E8_4393_BDE2_4B01B5379EA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanObj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanObj dialog

class CScanObj : public CDialog
{
// Construction
public:
	CScanObj(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanObj)
	enum { IDD = IDD_SCANOBJ };
		// NOTE: the ClassWizard will add data members here
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
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANOBJ_H__F84946D0_D8E8_4393_BDE2_4B01B5379EA1__INCLUDED_)
