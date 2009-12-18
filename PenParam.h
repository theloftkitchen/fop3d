#if !defined(AFX_PENPARAM_H__69DD3114_2767_4B0F_A651_700431516C4F__INCLUDED_)
#define AFX_PENPARAM_H__69DD3114_2767_4B0F_A651_700431516C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PenParam.h : header file
//
#include "MainFrm.h"
#include "MarkEzdDll.h"


extern BOOL m_IsLoad;
/////////////////////////////////////////////////////////////////////////////
// CPenParam dialog
class CDemoView;

class CPenParam : public CDialog
{
// Construction
public:
	CPenParam(CWnd* pParent = NULL);   // standard constructor


	CDemoView *m_pConnector;
	CMainFrame *m_pFrame;
	//pen parameters;

	int m_nPenNo;
	int m_nMarkLoop;
	double m_ndMarkSpeed;
	double m_ndPowerRatio;
	double m_ndCurrent;
	int m_nFreq;
	int m_nQPluse;
	int m_nStartTC;
	int m_nLaserOffTC;
	int m_nEndTC;
	int m_nPolyTC;
	double m_ndJumpSpeed;
	int m_nJumpPosTC;
	int m_nJumpDisTC;
	double m_ndEndComp;
	double m_ndAccDist;
	double m_ndPointTime;
	BOOL m_nbPulsePointMode;
	int m_nPulseNum;
	double m_ndFlySpeed;
	double m_tEndComp;
	double m_tAccDist;
	double m_tJumpSpeed;
	double m_tPointTime;






// Dialog Data
	//{{AFX_DATA(CPenParam)
	enum { IDD = IDD_PENPARA };
		// NOTE: the ClassWizard will add data members here

	CComboBox m_cStartTC;
	CComboBox m_cLaserOffTC;
	CComboBox m_cPolyTC;
	CComboBox m_cEndTC;
	CComboBox m_cJumpPosTC;
	CComboBox m_cJumpDistTC;

	CEdit m_cEndComp;
	CEdit m_cAccDist;
	CEdit m_cJumpSpeed;
	CEdit m_cPointTime;


	
	
	CButton m_cIsUseDefault;



	
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
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckdefault();
	afx_msg void OnSelchangeStarttc();
	afx_msg void OnSelchangeLaserofftc();
	afx_msg void OnSelchangePolytc();
	afx_msg void OnSelchangeEndtc();
	afx_msg void OnSelchangeJumppostc();
	afx_msg void OnSelchangeJumpdisttc();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PENPARAM_H__69DD3114_2767_4B0F_A651_700431516C4F__INCLUDED_)
