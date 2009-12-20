#if !defined(AFX_INPUTSCANNAME_H__982105A4_D56F_4B2C_99B6_E1BBF46AADB0__INCLUDED_)
#define AFX_INPUTSCANNAME_H__982105A4_D56F_4B2C_99B6_E1BBF46AADB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputScanName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputScanName dialog

class CInputScanName : public CDialog
{
// Construction
public:
	CInputScanName(CWnd* pParent = NULL);   // standard constructor
	_RecordsetPtr m_pRecord;
	BOOL m_nIsReplace;


// Dialog Data
	//{{AFX_DATA(CInputScanName)
	enum { IDD = IDD_InputScanName };
		// NOTE: the ClassWizard will add data members here
	CString m_nScanObjectName;
	CString m_nReturnName;
//	double m_nScanNumQuery;

	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputScanName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputScanName)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTSCANNAME_H__982105A4_D56F_4B2C_99B6_E1BBF46AADB0__INCLUDED_)
