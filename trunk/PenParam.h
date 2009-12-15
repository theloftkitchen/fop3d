#if !defined(AFX_PENPARAM_H__69DD3114_2767_4B0F_A651_700431516C4F__INCLUDED_)
#define AFX_PENPARAM_H__69DD3114_2767_4B0F_A651_700431516C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PenParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPenParam dialog

class CPenParam : public CDialog
{
// Construction
public:
	CPenParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPenParam)
	enum { IDD = IDD_PENPARA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPenParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPenParam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PENPARAM_H__69DD3114_2767_4B0F_A651_700431516C4F__INCLUDED_)
