// DemoEzd.h : main header file for the DEMOEZD application
//

#if !defined(AFX_DEMOEZD_H__8547BE64_3ECE_4EA3_A56E_CBCFA1A5479F__INCLUDED_)
#define AFX_DEMOEZD_H__8547BE64_3ECE_4EA3_A56E_CBCFA1A5479F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoEzdApp:
// See DemoEzd.cpp for the implementation of this class
//

class CDemoEzdApp : public CWinApp
{
public:
	CDemoEzdApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoEzdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoEzdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOEZD_H__8547BE64_3ECE_4EA3_A56E_CBCFA1A5479F__INCLUDED_)
