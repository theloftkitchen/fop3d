#if !defined(AFX_CHOOSEFIELD_H__748166FB_A318_4BD4_8BE4_2E3BC2EF4171__INCLUDED_)
#define AFX_CHOOSEFIELD_H__748166FB_A318_4BD4_8BE4_2E3BC2EF4171__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseField.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseField dialog

class CChooseField : public CDialog
{
// Construction
public:
	CChooseField(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseField)
	enum { IDD = IDD_CHOOSEFIELD };
		// NOTE: the ClassWizard will add data members here
	CString m_nReturnField;
	CListBox m_nAllFields;
	_RecordsetPtr m_pRecord;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseField)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseField)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkField();
	afx_msg void OnDestroy();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEFIELD_H__748166FB_A318_4BD4_8BE4_2E3BC2EF4171__INCLUDED_)
