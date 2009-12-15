#if !defined(AFX_CONTROLWND_H__96B4FC40_652C_468F_9BB9_1AED9D5DAF76__INCLUDED_)
#define AFX_CONTROLWND_H__96B4FC40_652C_468F_9BB9_1AED9D5DAF76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlWnd.h : header file
//
//#include "MainFrm.h"
//#include "CInputScanOName.h"
#include "InputScanName.h"
#include "PenParam.h"
#include "ScanObj.h"
#include "LoadEzdFile.h"
#include "MarkEzdDll.h"
#include "ChooseField.h"
/////////////////////////////////////////////////////////////////////////////
// CControlWnd form view


#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMainFrame;
class CControlWnd : public CFormView
{
public:
	CControlWnd();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CControlWnd)

// Form Data
public:
	//{{AFX_DATA(CControlWnd)
	enum { IDD = IDD_ControlWnd };
		// NOTE: the ClassWizard will add data members here
	CButton m_cAmp;
	CButton m_cShr;
	CButton m_cBack;
	CString m_tShowAngle;
	CSliderCtrl m_cRotateX;
	CSliderCtrl m_cRotateY;
	CSliderCtrl m_cRotateZ;
	double m_nDeltha;
	int m_nLighting;
	CString m_nScanObjectName;
	double m_nScanNum;
	int m_nDeleteNum;
	double m_nBasicDis;
	CString m_nLoadFileName;



	//}}AFX_DATA

// Attributes
public:
	CMainFrame *m_pFr;
	bool miniRotateFlag;
	CWinThread *m_pSaveThread;
	CWinThread *m_pMarkEntityThread;
	_RecordsetPtr m_pRecordset;

	bool m_bRDflag;
	int m_nCounter ;
	int m_nDrawCounter;
	CInputScanName dlgInputname;
	CPenParam dlgPenParam;
	CScanObj dlgScanObj;
	CLoadEzdFile dlgLoadFile;
	CChooseField dlgChooseField;
	BOOL m_nIsMarkFromFile;
	//variable on hardware
//	double fdata[MEASURETIMES]; //测量结果 2W 次



	//double  timeAr[15600];
	double *timeAr;


	





// Operations
public:
	void Count3DAxis(double *timeArray, int length);
	
	static UINT SaveDataFunc(LPVOID lpPara);
	static UINT MarkEntityFunc(LPVOID lpParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlWnd)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	
	void ReadFromDBFunc();
	
	void LaunchProgress(int num);
	virtual ~CControlWnd();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CControlWnd)
	afx_msg void OnAmp();
	afx_msg void OnShr();
	afx_msg void OnBack();
	afx_msg void OnLightOFF();
	afx_msg void OnLightON();
	afx_msg void OnSaveData();
	afx_msg void OnexitProgram();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCancelMode();
	afx_msg void OnReadgpib();
	afx_msg void OnUpdata();
	afx_msg void OnReadfromdb();
	afx_msg void OnLoadezdfile();
	afx_msg void OnPenparam();
	afx_msg void OnScanbasicobj();
	afx_msg void OnDestroy();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLWND_H__96B4FC40_652C_468F_9BB9_1AED9D5DAF76__INCLUDED_)
