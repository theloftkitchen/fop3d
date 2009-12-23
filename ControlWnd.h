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
class CDemoView;
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
	CButton m_cPenParam;
	CButton m_cReadFromGPIB;
		



	//}}AFX_DATA

// Attributes
public:
	CMainFrame *m_pFr;
	CDemoView* m_pCon;//pointer points to Veiw.
	bool miniRotateFlag;
	CWinThread *m_pSaveThread;
	CWinThread *m_pMarkEntityThread;
	_RecordsetPtr m_pRecordset;

	bool m_bRDflag; //a flag mark that the timearray is initialized.
	int m_nCounter ;//number of scan target time.
	
	CInputScanName dlgInputname;
	CPenParam dlgPenParam;
	CScanObj dlgScanObj;
	CLoadEzdFile dlgLoadFile;
	CChooseField dlgChooseField;

//	double *timeAr;//instance to develop,will be deleted by the end.
	/*
	double DataX[MEASURETIMES];
		double DataY[MEASURETIMES];
		double DataZ[MEASURETIMES];*/
	
	int m_nDrawCounter;//number of points to display.

	//some variables about gpib

	short  Buffer[120000];             /* Read buffer							 */
	double fdata[MEASURETIMES]; //测量结果 2W 次
	//some array to be stored in DB;
	double DataTheta[MEASURETIMES];
	double DataPhy[MEASURETIMES];
	double DataDist[MEASURETIMES];
	



	





// Operations
public:
	void Count3DAxis(double *timeArray, int length);
	
	static UINT SaveDataFunc(LPVOID lpPara);
	static UINT MarkEntityFunc(LPVOID lpParam);
	static UINT UpdataDataFunc(LPVOID lpParam);

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
	void ReCountFromDb(double * angleH,double *angleV,double  *Dist, int length);
	void NormalizeData(double *dx,double *dy, double *dz,int length);
	void Convert(int mode , int expd , int samples ,int index );
	bool isInsert;
	
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
	afx_msg void OnReadgpib();
	afx_msg void OnUpdata();
	afx_msg void OnReadfromdb();
	afx_msg void OnLoadezdfile();
	afx_msg void OnPenparam();
	afx_msg void OnScanbasicobj();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLWND_H__96B4FC40_652C_468F_9BB9_1AED9D5DAF76__INCLUDED_)
