// demo.h : main header file for the DEMO application
//

#if !defined(AFX_DEMO_H__78802C02_E99A_4E84_876C_8D3F5BC0734B__INCLUDED_)
#define AFX_DEMO_H__78802C02_E99A_4E84_876C_8D3F5BC0734B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#pragma comment(lib, "opengl32")
//#pragma comment(lib, "glu32")
//#pragma comment(lib, "glut32")
#include <gl/glu.h>
#include <gl/gl.h>
#include <gl/glaux.h>
#include "glut.h"
#include "LoginDlg.h"

const int MESSAGE_STEPPRO = WM_USER + 102;
const int MEASURETIMES = 30000;

/////////////////////////////////////////////////////////////////////////////
// CDemoApp:
// See demo.cpp for the implementation of this class
//

class CDemoApp : public CWinApp
{

	

public:
	_ConnectionPtr m_pConnection;
	CLoginDlg dlgLogin;


	CDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_H__78802C02_E99A_4E84_876C_8D3F5BC0734B__INCLUDED_)
