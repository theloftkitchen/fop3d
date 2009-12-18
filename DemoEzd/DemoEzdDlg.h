// DemoEzdDlg.h : header file
//

#if !defined(AFX_DEMOEZDDLG_H__D5C35BA8_57CF_4D71_B01B_C281D4F2E537__INCLUDED_)
#define AFX_DEMOEZDDLG_H__D5C35BA8_57CF_4D71_B01B_C281D4F2E537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoEzdDlg dialog
#include "MarkEzdDll.h"

class CDemoEzdDlg : public CDialog
{
// Construction
public:
	CDemoEzdDlg(CWnd* pParent = NULL);	// standard constructor

	HINSTANCE m_hEzdDLL;//DLLµ÷ÓÃ¾ä±ú
	
	LMC1_INITIAL       lmc1_Initial;
	LMC1_CLOSE         lmc1_Close;
	LMC1_LOADEZDFILE   lmc1_LoadEzdFile;
	LMC1_MARK          lmc1_Mark;
	LMC1_MARKENTITY    lmc1_MarkEntity;
	LMC1_GETPREVBITMAP lmc1_GetPrevBitmap;

	LMC1_READPORT  lmc1_ReadPort;
	LMC1_WRITEPORT lmc1_WritePort;

	LMC1_SETDEVCFG     lmc1_SetDevCfg; 
	LMC1_SETHATCHPARAM lmc1_SetHatchParam;
	LMC1_SETFONTPARAM  lmc1_SetFontParam;
	LMC1_GETPENPARAM   lmc1_GetPenParam;
	LMC1_SETPENPARAM   lmc1_SetPenParam;
	LMC1_CLEARENTLIB   lmc1_ClearEntLib;
	LMC1_ADDTEXTTOLIB  lmc1_AddTextToLib;
	LMC1_ADDFILETOLIB  lmc1_AddFileToLib;
	LMC1_ADDBARCODETOLIB   lmc1_AddBarCodeToLib;
	LMC1_CHANGETEXTBYNAME  lmc1_ChangeTextByName;
	LMC1_AXISMOVETO        lmc1_AxisMoveTo;	
	LMC1_AXISCORRECTORIGIN lmc1_AxisCorrectOrigin;	
	LMC1_GETAXISCOOR       lmc1_GetAxisCoor;
	LMC1_SAVEENTLIBTOFILE  lmc1_SaveEntLibToFile;

	

	void OnDrawPreview();
	CBitmap* m_pPrevBmp;

	void UpdatePrevBmp();
// Dialog Data
	//{{AFX_DATA(CDemoEzdDlg)
	enum { IDD = IDD_DEMOEZD_DIALOG };
	CString	m_strFileName;
	CString	m_strEntName;
	CString	m_strText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoEzdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoEzdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButtonRun();
	afx_msg void OnDestroy();
	afx_msg void OnButtonRunent();
	afx_msg void OnButtonAddtext();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOEZDDLG_H__D5C35BA8_57CF_4D71_B01B_C281D4F2E537__INCLUDED_)
