// PenParam.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "PenParam.h"
#include "demoView.h"
#include "demoDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPenParam dialog


CPenParam::CPenParam(CWnd* pParent /*=NULL*/)
	: CDialog(CPenParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPenParam)
		// NOTE: the ClassWizard will add member initialization here

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
	//}}AFX_DATA_INIT
	m_pConnector = NULL;
	m_pFrame = NULL;

	m_tEndComp = 0.0f;
	m_tAccDist = 0.0f;
	m_tJumpSpeed = 0.0f;
	m_tPointTime = 0.0f;



}


void CPenParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPenParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here

	DDX_Control(pDX,IDC_STARTTC,m_cStartTC);
	DDX_Control(pDX,IDC_LASEROFFTC,m_cLaserOffTC);
	DDX_Control(pDX,IDC_POLYTC,m_cPolyTC);
	DDX_Control(pDX,IDC_ENDTC,m_cEndTC);

	DDX_Control(pDX,IDC_JUMPPOSTC,m_cJumpPosTC);
	DDX_Control(pDX,IDC_JUMPDISTTC,m_cJumpDistTC);
	DDX_Text(pDX,IDC_ENDCOMP,m_tEndComp);
	DDX_Text(pDX,IDC_ACCDIST,m_tAccDist);
	DDX_Text(pDX,IDC_JUMPSPEED,m_tJumpSpeed);
	DDX_Text(pDX,IDC_POINTTIME,m_tPointTime);
	
	DDX_Control(pDX,IDC_ENDCOMP,m_cEndComp);
		DDX_Control(pDX,IDC_ACCDIST,m_cAccDist);
		DDX_Control(pDX,IDC_JUMPSPEED,m_cJumpSpeed);
		DDX_Control(pDX,IDC_POINTTIME,m_cPointTime);
	

	DDX_Control(pDX,IDC_CHECKDEFAULT,m_cIsUseDefault);





	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPenParam, CDialog)
	//{{AFX_MSG_MAP(CPenParam)
	ON_BN_CLICKED(IDC_CHECKDEFAULT, OnCheckdefault)
	ON_CBN_SELCHANGE(IDC_STARTTC, OnSelchangeStarttc)
	ON_CBN_SELCHANGE(IDC_LASEROFFTC, OnSelchangeLaserofftc)
	ON_CBN_SELCHANGE(IDC_POLYTC, OnSelchangePolytc)
	ON_CBN_SELCHANGE(IDC_ENDTC, OnSelchangeEndtc)
	ON_CBN_SELCHANGE(IDC_JUMPPOSTC, OnSelchangeJumppostc)
	ON_CBN_SELCHANGE(IDC_JUMPDISTTC, OnSelchangeJumpdisttc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenParam message handlers

void CPenParam::OnOK() 
{
	// TODO: Add extra validation here
//	
		UpdateData(true);


	m_pConnector->lmc1_SetPenParam(m_nPenNo,m_nMarkLoop,m_ndMarkSpeed,m_ndPowerRatio,m_ndCurrent,
		m_nFreq,m_nQPluse,m_nStartTC,m_nLaserOffTC,m_nEndTC,
		m_nPolyTC,m_ndJumpSpeed,m_nJumpPosTC,m_nJumpDisTC,m_ndEndComp,
		m_ndAccDist,m_ndPointTime,m_nbPulsePointMode,m_nPulseNum,m_ndFlySpeed
		
									);
	if (BST_CHECKED == IsDlgButtonChecked( IDC_CHECKDEFAULT))
	{
	}
	else
	{
		int nSaveMessage = MessageBox(_T("已经将参数据保存至内存,是否保存当前设置至文件"),_T("提示"),32+4+0);
		if (IDYES == nSaveMessage)
		{
			CFileDialog dlg(FALSE,_T(""),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Ezcad file(*.ezd)|*.ezd|"));
			
			if(dlg.DoModal()==IDOK)
			{
				CString strFileName = dlg.GetPathName();
				
				TCHAR szFile[256];
				_tcscpy(szFile,strFileName);
				int nErr = m_pConnector->lmc1_SaveEntLibToFile(szFile);
				if(nErr!=LMC1_ERR_SUCCESS)
				{
					AfxMessageBox(_T("Read ezdfile failed!"));				
				}
			}
			
			
	}
	}
	
		UpdateData(FALSE);

	
		m_IsLoad = FALSE;
	

	



	CDialog::OnOK();
}

BOOL CPenParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_pFrame = (CMainFrame*)AfxGetMainWnd();
	m_pConnector = m_pFrame->m_pTreeView;
	CDemoDoc *pDoc = m_pConnector->GetDocument();


	
	
	if (m_IsLoad == FALSE)
			{
				AfxMessageBox(_T("请先载入模型文件!"));
				SendMessage(WM_CLOSE,0,0);
				
		
			}
	
	
	//initial variable

	else
	{

	
	int i = 0;
	CString tmp;
	for ( i = 0;i<=1000;i+=10)
	{
		tmp.Format(_T("%d"),i);
		((CComboBox*)GetDlgItem(IDC_STARTTC))->AddString(tmp);
		((CComboBox*)GetDlgItem(IDC_LASEROFFTC))->AddString(tmp);
		((CComboBox*)GetDlgItem(IDC_ENDTC))->AddString(tmp);
		((CComboBox*)GetDlgItem(IDC_JUMPDISTTC))->AddString(tmp);
		((CComboBox*)GetDlgItem(IDC_JUMPPOSTC))->AddString(tmp);
		((CComboBox*)GetDlgItem(IDC_POLYTC))->AddString(tmp);
		
		
	}
	
		




			
	


/*
	m_pConnector->lmc1_GetPenParam(m_nPenNo,m_nMarkLoop,m_ndMarkSpeed,m_ndPowerRatio,m_ndCurrent,
									m_nFreq,m_nQPluse,m_nStartTC,m_nLaserOffTC,m_nEndTC,
									m_nPolyTC,m_ndJumpSpeed,m_nJumpPosTC,m_nJumpDisTC,m_ndEndComp,
									m_ndAccDist,m_ndPointTime,m_nbPulsePointMode,m_nPulseNum,m_ndFlySpeed

									);
	m_tEndComp = m_ndEndComp;
	m_tAccDist = m_ndAccDist;
	m_tJumpSpeed = m_ndJumpSpeed;
	m_tPointTime  = m_ndPointTime;
*/
	m_nPenNo = pDoc->m_nPenNo;
	m_nMarkLoop = pDoc->m_nMarkLoop;
	m_ndMarkSpeed = pDoc->m_ndMarkSpeed;
	m_ndPowerRatio = pDoc->m_ndPowerRatio;
	m_nFreq = pDoc->m_nFreq;
	m_nQPluse = pDoc->m_nQPluse;
	m_nStartTC = pDoc->m_nStartTC;
	m_nLaserOffTC = pDoc->m_nLaserOffTC;
	m_nEndTC = pDoc->m_nEndTC;
	m_nPolyTC = pDoc->m_nPolyTC;
	m_ndJumpSpeed = pDoc->m_ndJumpSpeed;
	m_nJumpPosTC = pDoc->m_nJumpPosTC;
	m_nJumpDisTC = pDoc->m_nJumpDisTC;
	m_ndEndComp = pDoc->m_ndEndComp;
	m_ndAccDist = pDoc->m_ndAccDist;
	m_ndPointTime = pDoc->m_ndPointTime;
	m_nbPulsePointMode = pDoc->m_nbPulsePointMode;
	m_nPulseNum = pDoc->m_nPulseNum;
	m_ndFlySpeed = pDoc->m_ndFlySpeed;
	//edit
	m_tEndComp = m_ndEndComp;
	m_tAccDist = m_ndAccDist;
	m_tJumpSpeed = m_ndJumpSpeed;
	m_tPointTime  = m_ndPointTime;

	CString tmpString;
	tmpString.Format(_T("%d"),m_nStartTC);
	m_cStartTC.SelectString(0,tmpString);
	tmpString.Format(_T("%d"),m_nLaserOffTC);
	m_cLaserOffTC.SelectString(0,tmpString);
	tmpString.Format(_T("%d"),m_nPolyTC);
	m_cPolyTC.SelectString(0,tmpString);
	tmpString.Format(_T("%d"),m_nEndTC);
	m_cEndTC.SelectString(0,tmpString);
	tmpString.Format(_T("%d"),m_nJumpPosTC);
	m_cJumpPosTC.SelectString(0,tmpString);
	tmpString.Format(_T("%d"),m_nJumpDisTC);
	m_cJumpDistTC.SelectString(0,tmpString);



	((CButton*)GetDlgItem(IDC_CHECKDEFAULT))->SetCheck(TRUE);
	
	
	m_cStartTC.EnableWindow(FALSE);
	m_cLaserOffTC.EnableWindow(FALSE);
	
	m_cPolyTC.EnableWindow(FALSE);
	m_cEndTC.EnableWindow(FALSE);
	m_cJumpDistTC.EnableWindow(FALSE);
	m_cJumpPosTC.EnableWindow(FALSE);
	
	
	
	
	
	m_cAccDist.EnableWindow(FALSE);
	m_cEndComp.EnableWindow(FALSE);
	m_cJumpSpeed.EnableWindow(FALSE);
	m_cPointTime.EnableWindow(FALSE);
	}
	
	

	






	


	





	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPenParam::OnCheckdefault() 
{
	// TODO: Add your control notification handler code here
	if (m_cIsUseDefault.GetCheck() == FALSE)
	{
		m_cStartTC.EnableWindow(TRUE);

		m_cLaserOffTC.EnableWindow(TRUE);
		
		
		m_cPolyTC.EnableWindow(TRUE);
		m_cEndTC.EnableWindow(TRUE);
		m_cJumpDistTC.EnableWindow(TRUE);
		m_cJumpPosTC.EnableWindow(TRUE);
		
		
		
		
		
		m_cAccDist.EnableWindow(TRUE);
		m_cEndComp.EnableWindow(TRUE);
		m_cJumpSpeed.EnableWindow(TRUE);
	m_cPointTime.EnableWindow(TRUE);

	}
	else
	{
		m_cStartTC.EnableWindow(FALSE);
		
		m_cLaserOffTC.EnableWindow(FALSE);
		
		
		m_cPolyTC.EnableWindow(FALSE);
		m_cEndTC.EnableWindow(FALSE);
		m_cJumpDistTC.EnableWindow(FALSE);
		m_cJumpPosTC.EnableWindow(FALSE);
		
		
		
		
		
		m_cAccDist.EnableWindow(FALSE);
		m_cEndComp.EnableWindow(FALSE);
		m_cJumpSpeed.EnableWindow(FALSE);
	m_cPointTime.EnableWindow(FALSE);


	}

}



void CPenParam::OnSelchangeStarttc() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cStartTC.GetCurSel();
	if ( CB_ERR == nIndex)
	{
		MessageBox(_T("请选择后再得到内容!"));

	}
	else
	{
		CString str;
		m_cStartTC.GetLBText(nIndex,str);
		m_nStartTC = atol(_bstr_t(str));

	}

}

void CPenParam::OnSelchangeLaserofftc() 
{
	// TODO: Add your control notification handler code here
	
	int nIndex = m_cLaserOffTC.GetCurSel();
	if ( CB_ERR == nIndex)
	{
		MessageBox(_T("请选择后再得到内容!"));
		
	}
	else
	{
		CString str;
		m_cLaserOffTC.GetLBText(nIndex,str);
		m_nLaserOffTC = atol(_bstr_t(str));
		
	}
}

void CPenParam::OnSelchangePolytc() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cPolyTC.GetCurSel();
	if ( CB_ERR == nIndex)
	{
		MessageBox(_T("请选择后再得到内容!"));
		
	}
	else
	{
		CString str;
		m_cPolyTC.GetLBText(nIndex,str);
		m_nPolyTC = atol(_bstr_t(str));
		
	}
}

void CPenParam::OnSelchangeEndtc() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cEndTC.GetCurSel();
	if ( CB_ERR == nIndex)
	{
		MessageBox(_T("请选择后再得到内容!"));
		
	}
	else
	{
		CString str;
		m_cEndTC.GetLBText(nIndex,str);
		m_nEndTC = atol(_bstr_t(str));
		
	}
}

void CPenParam::OnSelchangeJumppostc() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cJumpPosTC.GetCurSel();
	if ( CB_ERR == nIndex)
	{
		MessageBox(_T("请选择后再得到内容!"));
		
	}
	else
	{
		CString str;
		m_cJumpPosTC.GetLBText(nIndex,str);
		m_nJumpPosTC = atol(_bstr_t(str));
		
	}
}

void CPenParam::OnSelchangeJumpdisttc() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_cJumpDistTC.GetCurSel();
	if ( CB_ERR == nIndex)
	{
		MessageBox(_T("请选择后再得到内容!"));
		
	}
	else
	{
		CString str;
		m_cJumpDistTC.GetLBText(nIndex,str);
		m_nJumpDisTC = atol(_bstr_t(str));
		
	}
}

void CPenParam::OnCancel() 
{
	// TODO: Add extra cleanup here
	SendMessage(WM_CLOSE,0,0);

	CDialog::OnCancel();
}
