// demoDoc.h : interface of the CDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMODOC_H__64E83397_DD08_407C_9AD7_A3DAB544A845__INCLUDED_)
#define AFX_DEMODOC_H__64E83397_DD08_407C_9AD7_A3DAB544A845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemoDoc : public CDocument
{
protected: // create from serialization only
	CDemoDoc();
	DECLARE_DYNCREATE(CDemoDoc)

// Attributes
public:
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

	//array pass to View to display
	double DataX[MEASURETIMES];
	double DataY[MEASURETIMES];
	double DataZ[MEASURETIMES];
	int m_nDrawCounter;
	
	


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODOC_H__64E83397_DD08_407C_9AD7_A3DAB544A845__INCLUDED_)
