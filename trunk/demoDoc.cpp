// demoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "demo.h"

#include "demoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc construction/destruction

CDemoDoc::CDemoDoc()
{
	// TODO: add one-time construction code here
	m_nbPulsePointMode = FALSE;
	m_ndAccDist = 0;
	m_ndCurrent = 0;
	m_ndEndComp = 0;
	m_ndFlySpeed =0;
	m_ndJumpSpeed = 0;
	m_ndMarkSpeed = 0;
	m_ndPointTime = 0;
	m_ndPowerRatio = 0;
	m_nEndTC = 0;
	m_nFreq = 0;
	m_nJumpDisTC = 0;
	m_nJumpPosTC = 0;
	m_nLaserOffTC = 0;
	m_nMarkLoop = 0;
	m_nPenNo = 0;
	m_nPolyTC = 0;
	m_nPulseNum = 0;
	m_nQPluse = 0;
	m_nStartTC = 0;
	for (int i =0;i<MEASURETIMES; ++i)
	{
		DataX[i] = .0f;
		DataY[i] = .0f;
		DataZ[i] = .0f;
		

	}
	m_nDrawCounter = 0;

}

CDemoDoc::~CDemoDoc()
{
}

BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDemoDoc serialization

void CDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc diagnostics

#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc commands
