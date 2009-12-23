// ControlWnd.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ControlWnd.h"
#include "demoView.h"
#include "demoDoc.h"
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

//add something about gpib
//#include "AxisTransform.h"
#include "ni488.h"
#include "windows.h"


#define pa 3.14159265358979

FILE *out;
///gpib

///end

double *timeAr;		//testing




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlWnd


/*
vector<double>DataX(70000);
vector<double>DataY(70000);
vector<double>DataZ(70000);
*/

//extern _ConnectionPtr theApp.theApp.m_pConnection;
extern CDemoApp theApp;
double CountDistance(double retime);
double CountAngle(double angle1, double angle2);

///////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CControlWnd, CFormView)

CControlWnd::CControlWnd()
: CFormView(CControlWnd::IDD)
{
	//{{AFX_DATA_INIT(CControlWnd)
	// NOTE: the ClassWizard will add member initialization here
	m_nLighting = -1;
	//}}AFX_DATA_INIT
	m_bRDflag = FALSE;
	m_nCounter = 0 ;
	m_nDeltha = 1.0;
	m_nDrawCounter = 0;
	m_nScanObjectName = _T("");
	m_nScanNum = 160.0;
	m_nDeleteNum = 3;
	m_nBasicDis = 1000.0f;
	m_nLoadFileName = _T("");
	m_nDrawCounter = 0;
	//	m_nIsMarkFromFile = FALSE;
	
	// initialize function pointer
	for (int i =0 ;i<MEASURETIMES;++i)
	{
		fdata[i] = 0;
		DataTheta[i] = 0;
		DataPhy[i] = 0;
		DataDist[i] = 0;
			
	}

	
	
	
}

CControlWnd::~CControlWnd()
{
}

void CControlWnd::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CControlWnd)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_AMP,m_cAmp);
	DDX_Control(pDX,IDC_SHR,m_cShr);
	DDX_Control(pDX,IDC_BACK,m_cBack);
	DDX_Control(pDX,IDC_RotateX,m_cRotateX);
	DDX_Control(pDX,IDC_RotateY,m_cRotateY);
	DDX_Control(pDX,IDC_RotateZ,m_cRotateZ);
	DDX_Radio(pDX,IDC_LightOFF,m_nLighting);
	DDX_Text(pDX,IDC_DELTHA,m_nDeltha);
	DDV_MinMaxDouble(pDX,m_nDeltha,.0,1.0);
	DDX_Text(pDX,IDC_SCAN,m_nScanNum);
	DDV_MinMaxDouble(pDX,m_nScanNum,160.0,256.0);
	DDX_Text(pDX,IDC_DELETENUM,m_nDeleteNum);
	DDX_Control(pDX,IDC_PENPARAM,m_cPenParam);
	DDX_Control(pDX,IDC_READGPIB,m_cReadFromGPIB);
	
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CControlWnd, CFormView)
//{{AFX_MSG_MAP(CControlWnd)
ON_BN_CLICKED(IDC_AMP, OnAmp)
ON_BN_CLICKED(IDC_SHR, OnShr)
ON_BN_CLICKED(IDC_BACK, OnBack)
ON_BN_CLICKED(IDC_LightOFF, OnLightOFF)
ON_BN_CLICKED(IDC_LightON, OnLightON)
ON_BN_CLICKED(IDC_SaveData, OnSaveData)
ON_BN_CLICKED(IDC_exitProgram, OnexitProgram)
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_READGPIB, OnReadgpib)
ON_BN_CLICKED(IDC_UPDATA, OnUpdata)
ON_BN_CLICKED(IDC_READFROMDB, OnReadfromdb)
ON_BN_CLICKED(IDC_LOADEZDFILE, OnLoadezdfile)
ON_BN_CLICKED(IDC_PENPARAM, OnPenparam)
ON_BN_CLICKED(IDC_SCANBASICOBJ, OnScanbasicobj)
ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlWnd diagnostics

#ifdef _DEBUG
void CControlWnd::AssertValid() const
{
	CFormView::AssertValid();
}

void CControlWnd::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CControlWnd message handlers

void CControlWnd::OnAmp() 
{
	// TODO: Add your control notification handler code here
	this->m_pFr->m_pTreeView->zoom += 1.50f;
	this->m_pFr->m_pTreeView->Invalidate();
}

void CControlWnd::OnShr() 
{
	// TODO: Add your control notification handler code here
	this->m_pFr->m_pTreeView->zoom -=1.50f;
	this->m_pFr->m_pTreeView->Invalidate();
	
	
}

void CControlWnd::OnBack() 
{
	// TODO: Add your control notification handler code here
	this->m_pFr->m_pTreeView->zoom =-4.50f;
	this->m_pFr->m_pTreeView->Invalidate();
	
}

void CControlWnd::OnLightOFF() 
{
	// TODO: Add your control notification handler code here
	this->m_pFr->m_pTreeView->ENABLELIGHT = FALSE;
	this->m_pFr->m_pTreeView->Invalidate();
}

void CControlWnd::OnLightON() 
{
	// TODO: Add your control notification handler code here
	this->m_pFr->m_pTreeView->ENABLELIGHT = TRUE;
	this->m_pFr->m_pTreeView->Invalidate();
}

void CControlWnd::OnSaveData() 
{
	// TODO: Add your control notification handler code here
	if(dlgInputname.DoModal() == IDOK)
	{
		if (dlgInputname.m_nReturnName == "")
		{
			AfxMessageBox(_T("扫描物体名称不能为空!"));
		//	SendMessage(WM_CLOSE,0,0);
		}
		else
		{

			m_nScanObjectName = dlgInputname.m_nReturnName;
			if (dlgInputname.m_nIsReplace == TRUE)
			{
				m_pSaveThread = AfxBeginThread(UpdataDataFunc,this);

			}
			else
			{
				m_pSaveThread = AfxBeginThread(SaveDataFunc,this);

			}
			

		}

		
	}
	
	//add 进度条...
	
	/*	if(m_bRDflag)
	{*/
			
				
				
				/*
				}
				else
				{
				if(m_pSaveThread)
				{
				m_pSaveThread->PostThreadMessage(WM_CLOSE,0,0);
				::WaitForSingleObject(m_pSaveThread->m_hThread,INFINITE);
				m_pSaveThread = NULL;
				}
}*/
				
				
				UpdateData(FALSE);
				
				
				
				
				
}

void CControlWnd::OnexitProgram() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	
	
	this->m_pFr->SendMessage(WM_CLOSE);
}

void CControlWnd::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	this->m_pFr = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	m_pCon = m_pFr->m_pTreeView;
	//		
	m_cPenParam.EnableWindow(FALSE);
	m_cReadFromGPIB.EnableWindow(FALSE);
	
	
	
	
	
	
	
	
	
	
	///test...
	int i =0;
	
	timeAr = new double[15600];
	double j=.0f;
	int k=0;
	for(i=0 ;i<15600;++i)
	{
		
		if(k == 162)
		{
			k = 0;
			j = .0f;
			
		}
		k++;
		j=j+0.000000001;
		
		
		
		timeAr[i] = .0000067f+j;
	}
	
	
	///test end
	
	m_cRotateX.SetRange(-180,180);
	m_cRotateY.SetRange(-180,180);
	m_cRotateZ.SetRange(-180,180);
	m_cRotateX.SetPos(0);
	m_cRotateY.SetPos(0);
	m_cRotateZ.SetPos(0);
	m_nLighting = 0;
	UpdateData(FALSE);
	
	
}

void CControlWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	float anglex,angley,anglez;
	
	this->m_pFr->m_pTreeView->m_fRotateX=
		anglex = (FLOAT)m_cRotateX.GetPos();
	this->m_pFr->m_pTreeView->m_fRotateY = 
		angley = (FLOAT)m_cRotateY.GetPos();
	this->m_pFr->m_pTreeView->m_fRotateZ = 
		anglez = (FLOAT)m_cRotateZ.GetPos();
	CString m_aRotate;
	m_aRotate.Format(_T("x:%f,Y;%f,Z:%f"),anglex,angley,anglez);
	this->GetDlgItem(IDC_SHowGAngle)->SetWindowText(m_aRotate);
	
	UpdateData(FALSE);
	this->m_pFr->m_pTreeView->Invalidate();
	
	
	
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


UINT CControlWnd::SaveDataFunc(LPVOID lpParam)
{
	
	CControlWnd *me = (CControlWnd *)lpParam;
	//open the database;
	
	me->isInsert=true;
	//read data from database;
	
	
	me->m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString vSQLIN;
	_variant_t RecordAffected;
	CString strFor;
	
	int i=0;
	int m = 0,n = 0;
	theApp.m_pConnection->BeginTrans();
	for(i=0;i<me->m_nDrawCounter;++i)
	{
		vSQLIN.Format(_T("insert into Target values('%s',%f,%f,%f,%f)"),me->m_nScanObjectName,me->m_nScanNum,me->DataTheta[i],me->DataPhy[i],me->DataDist[i]);
		try
		{
			
			theApp.m_pConnection->Execute(_bstr_t(vSQLIN),&RecordAffected,adCmdText);
			
		}
		catch(_com_error e)
		{
			theApp.m_pConnection->RollbackTrans();
			AfxMessageBox(e.ErrorMessage());
		}
		if (0 == n || n == 156/*(m_nScanNum*m_nScanNum)/100,正确*/ )// will be modified........
		{
			++m;
			me->LaunchProgress(m);
			
			n = 0;
			
		}
		++n;
		
	}
	theApp.m_pConnection->CommitTrans();			
	
	
	AfxMessageBox(_T("insert successfully"));
	//	me->m_pRecordset->close();
	me->m_pRecordset = NULL;
	me->isInsert=false;
	return 0;
}

UINT CControlWnd::UpdataDataFunc(LPVOID lpParam)
{
	CControlWnd *me = (CControlWnd *)lpParam;
	//open the database;
	
	
	//update from database;
	
	
	me->m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString vSQLIN;
	_variant_t RecordAffected;
	CString strFor;
	
	//	vector<double>::iterator Poiter;
	int i=0;
	int m = 0,n = 0;
	theApp.m_pConnection->BeginTrans();
	vSQLIN.Format(_T("delete from Target where TargetName = '%s'"),me->m_nScanObjectName);
	try
	{
		theApp.m_pConnection->Execute(_bstr_t(vSQLIN),&RecordAffected,adCmdText);
	}
	catch (_com_error e)
	{
		theApp.m_pConnection->RollbackTrans();
		AfxMessageBox(e.ErrorMessage());
		
	}
	theApp.m_pConnection->CommitTrans();
	me->m_pRecordset = NULL;
	vSQLIN = _T("");
	theApp.m_pConnection->BeginTrans();


	for(i=0;i<me->m_nDrawCounter;++i)
	{
		vSQLIN.Format(_T("insert into Target values('%s',%f,%f,%f,%f)"),me->m_nScanObjectName,me->m_nScanNum,me->DataTheta[i],me->DataPhy[i],me->DataDist[i]);
		try
		{
			
			theApp.m_pConnection->Execute(_bstr_t(vSQLIN),&RecordAffected,adCmdText);
			
		}
		catch(_com_error e)
		{
			theApp.m_pConnection->RollbackTrans();
			AfxMessageBox(e.ErrorMessage());
		}
		if (0 == n || n == 156/*(m_nScanNum*m_nScanNum)/100,正确*/ )
		{
			++m;
			me->LaunchProgress(m);
			
			n = 0;
			
		}
		++n;
		
	}
	theApp.m_pConnection->CommitTrans();			
	
	
	AfxMessageBox(_T("insert successfully"));

	me->m_pRecordset = NULL;

	return 0;
}

/************************************************************************/
/* read from gpib                                                       */
/************************************************************************/
void CControlWnd::OnReadgpib() 
{
	if (m_nLoadFileName == _T(""))
	{
		MessageBox(_T("请先装载扫描模型文件!"),_T("警告"),0+16);
		return;
	}
	MessageBox(_T("将要开始扫描数据,请点击'确定'开始"),_T("提示"),0+48+0);

	//initialize array for re-read from gpib
	int i=0;
	for (i =0 ;i<MEASURETIMES;++i)
	{
		fdata[i] = 0;
		DataTheta[i] = 0;
		DataPhy[i] = 0;
		DataDist[i] = 0;
		
	}
	
	///initialize gpib
	int Device ;                   /* Device unit descriptor                  */
	int BoardIndex;              /* Interface Index (GPIB0=0,GPIB1=1,etc.)  */
	

	int samples = 0;
	m_bRDflag = FALSE;
	m_nCounter = 0;//save displaying number of points;
//	int i =0 ;
	int   PrimaryAddress = 1;      /* Primary address of the device           */
	int   SecondaryAddress = 0;    /* Secondary address of the device         */
	
	
	
	
	
	/*****************************************************************************
	* Initialization - Done only once at the beginning of your application.
	*****************************************************************************/
	
	Device = ibdev(                /* Create a unit descriptor handle         */
		BoardIndex,              /* Board Index (GPIB0 = 0, GPIB1 = 1, ...) */
		PrimaryAddress,          /* Device primary address                  */
		SecondaryAddress,        /* Device secondary address                */
		T30s,                    /* Timeout setting (T10s = 10 seconds)     */
		1,                       /* Assert EOI line at end of write         */
		0);                      /* EOS termination mode                    */
	
	
	
	
	ibclr(Device);                 /* Clear the device                        */
	
	/*
	ibdma(Device,1);
	if(ibsta & ERR)
	{
	GpibError("ibdma Error");
	}
	*/
	/*****************************************************************************
	* Main Application Body - Write the majority of your GPIB code here.
	*****************************************************************************/
	

	
	
	ibwrt(Device,"*RST;MODE 0;SRCE 0;ARMM 1;SIZE 1",32);

	for(int a=0;a<10000;a++)
	{
	}
	
	
	
	//start to MarkEntity thread;
	m_pMarkEntityThread = AfxBeginThread(MarkEntityFunc,this);
	
	ibwrt(Device,"BDMP 30000",10);
	
	
	if((out = fopen("d:\\out.txt","wt+"))!=NULL)
	{
		
		ibrd(Device, Buffer,240000);     //Read up to 2000 bytes from the device   
		samples=ibcntl/8;
		m_nCounter=samples;
		if (ibsta & ERR) {
			//				GpibError("ibrd Error");
		}
		
		Convert(1,0,samples,0);
		
		
		for(int j = 0 ; j<samples;j++)
		{
			fprintf(out,"%d :%.14f  ",j,fdata[j]);
			fprintf(out,"\n");  
		}
		
		m_bRDflag=true;
		fprintf(out,"%d\n",m_nCounter);
	}
	fclose(out);
	
	/*****************************************************************************
	* Uninitialization - Done only once at the end of your application.
	*****************************************************************************/
	
	ibonl(Device, 0);              /* Take the device offline                 */
	
	
	
	//读取结束
	if(m_bRDflag == true)
	{
		Count3DAxis(fdata,m_nCounter);
		// m_pSaveThread = AfxBeginThread(SaveDataFunc,this);
//		NormalizeData(DataX,DataY,DataZ,m_nCounter);
		this->m_pFr->m_pTreeView->Invalidate();
	}
/*	if(m_pSaveThread)
	{
		m_pSaveThread->PostThreadMessage(WM_CLOSE,0,0);
		::WaitForSingleObject(m_pSaveThread->m_hThread,INFINITE);
		m_pSaveThread = NULL;
	}
	*/
	m_cPenParam.EnableWindow(FALSE);
	m_cReadFromGPIB.EnableWindow(FALSE);
	
	
}

void CControlWnd::OnUpdata() 
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	
	
		Count3DAxis(timeAr,15600);//15600应该变成扫描点数的平方.
//	Count3DAxis(fdata,m_nCounter);
	
//	NormalizeData(DataX,DataY,DataZ,m_nDrawCounter);
	
	this->m_pFr->m_pTreeView->Invalidate(FALSE);
	UpdateData();
	
}

void CControlWnd::Count3DAxis(double *timeArray, int length)
{
	
	
	
	
	int tmpnum =length;
	int  i = 0 ,j = 0;
	int u=0;
	int s=0,t=0;
	
	double angleHor; //theta
	double angleVer; //fai
	double tmpX;
	double tmpY;
	double tmpZ;
	CDemoDoc *pDoc = m_pCon->GetDocument();
	
	
	
	double tmpDistance=0;
	
	
	for(i=0;i<tmpnum;++i)
	{ 
		
		
		if (j == m_nScanNum)
		{
			i += m_nDeleteNum - 1;
			if (i >= tmpnum)
			{
				break;//不确定这样行不行,待确认...
			}
			j = 0;
			t = 0;
			++s;
			continue;
		}
		else
		{
			
			
			
			tmpDistance = CountDistance(timeArray[i]);;		//distance
			if (tmpDistance >= (m_nBasicDis - 350.0) && tmpDistance <= (m_nBasicDis+350.0))
			{
				angleHor = 5.0-(s*10/m_nScanNum);			//angle should add another constant that is not uncertain.
				if((s+1)%2==0)
					angleVer = -(((t+0.5)*10/m_nScanNum)-5.0);
				else
					angleVer = -(5.0-((t+0.5)*10/m_nScanNum));			
				//transform to hudu.
				angleHor = angleHor*pa/180.0;
				angleVer = angleVer*pa/180.0;
				//count and save to container;
				
				tmpX = tmpDistance*sinf(angleHor)/CountAngle(angleHor,angleVer);
				
			//	DataX[u] = tmpX;
				pDoc->DataX[u] = tmpX;
				tmpY = tmpDistance*cosf(angleHor)*tanf(angleVer)/CountAngle(angleHor,angleVer);
				
			//	DataY[u] = tmpY;
				pDoc->DataY[u] = tmpY;
				tmpZ = tmpDistance*cosf(angleHor)/CountAngle(angleHor,angleVer);
				
				//DataZ[u] = tmpZ;
				pDoc->DataZ[u] = tmpZ;
				
				//these data should be saved to DB
				DataTheta[u] = angleHor;
				DataPhy[u] = angleVer;
				DataDist[u] = tmpDistance;
				//end;
				++j;
				++t;//横轴坐标
				++u;
			}
			else
				continue;
			
			
		}
		
		
	}
	
		m_nDrawCounter = u;	
		pDoc->m_nDrawCounter = u;
		NormalizeData(pDoc->DataX,pDoc->DataY,pDoc->DataZ,m_nDrawCounter);
		
}



void CControlWnd::OnReadfromdb() 
{
	// TODO: Add your control notification handler code here
	this->m_pFr->InvalidateAllWnd();
	
	if(dlgChooseField.DoModal() == IDOK)
	{
		m_nScanObjectName = dlgChooseField.m_nReturnField;
		ReadFromDBFunc();
		
		this->m_pFr->m_pTreeView->Invalidate();
	}
	
}



void CControlWnd::LaunchProgress(int num)
{
	::SendMessage(this->m_pFr->m_hWnd,MESSAGE_STEPPRO,num,0);
	
}


void CControlWnd::ReadFromDBFunc()
{

	
	for (int i = 0; i<MEASURETIMES; ++i)
	{
		DataDist[i] = .0f;
		DataPhy[i] = .0f;
		DataTheta[i] = .0f;

		
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));
	CString vSQLIN;
	_variant_t RecordAffected;
	CString strFor;
	int n = 0;
	int m = 0;
	strFor.Format(_T("select TargetTheta,TargetPhy,TargetDist from Target where TargetName = '%s'"),m_nScanObjectName);
	m_pRecordset = theApp.m_pConnection->Execute(_bstr_t(strFor),&RecordAffected,adCmdText);
	if((m_pRecordset->BOF) && (m_pRecordset->adoEOF))
	{
		AfxMessageBox(_T("没有扫描这个物体!"));
		m_pRecordset->Close();
		return;
	}
	_variant_t vFileValue;
	//CString csdx,csdy,csdz;
	i = 0;
	
	while (VARIANT_FALSE == m_pRecordset->adoEOF)
	{
		vFileValue = m_pRecordset->GetCollect("TargetTheta");
		DataTheta[i] =atof(_bstr_t(vFileValue));
		//	vFileValue.clear();
		vFileValue = m_pRecordset->GetCollect("TargetPhy");
		DataPhy[i] = atof(_bstr_t(vFileValue));
		//	vFileValue.clear();
		vFileValue = m_pRecordset->GetCollect("TargetDist");
		DataDist[i] = atof(_bstr_t(vFileValue));
		//	vFileValue.clear();
		
		
		if (0 == n || n == 156/*(m_nScanNum*m_nScanNum)/100,正确*/ )//.....to modify
		{
			++m;
			::SendMessage(this->m_pFr->m_hWnd,MESSAGE_STEPPRO,m,0);
			n = 0;
			
		}
		++n;
		++i;
		m_pRecordset->MoveNext();
		
		
		
	}
	m_pRecordset->Close();
	
	
	m_nDrawCounter = i;
	ReCountFromDb(DataTheta,DataPhy,DataDist,m_nDrawCounter);

	
	
}

void CControlWnd::OnLoadezdfile() 
{
	// TODO: Add your control notification handler code here

	
	if (dlgLoadFile.DoModal() == IDOK )
	{
		if (dlgLoadFile.m_nReadFlag == TRUE)
		{
			m_nLoadFileName = dlgLoadFile.m_nReturnLoadFileName;
			m_cPenParam.EnableWindow(TRUE);
			m_cReadFromGPIB.EnableWindow(TRUE);
		}
		else
		{
			MessageBox(_T("没有打开模型文件!"),_T("提示"),0+48+0);
			SendMessage(WM_CLOSE,0,0);
		}
		
		//			m_nIsMarkFromFile = TRUE;
		
	}
	else
	{
		

		SendMessage(WM_CLOSE,0,0);
		
	}
	UpdateData(FALSE);
	
}


void CControlWnd::OnPenparam() 
{
	// TODO: Add your control notification handler code here
	dlgPenParam.DoModal();
}

void CControlWnd::OnScanbasicobj() 
{
	// TODO: Add your control notification handler code here
	if (dlgScanObj.DoModal() == IDOK)
	{
		m_nBasicDis = dlgScanObj.m_nReturnDistance;
	}
	else
	{
		
		m_nBasicDis = 1000.0f;
		
	}
	
}

void CControlWnd::OnDestroy() 
{
	CFormView::OnDestroy();
	// TODO: Add your message handler code here
	
}



UINT CControlWnd::MarkEntityFunc(LPVOID lpParam)
{
	CControlWnd *pThis = (CControlWnd*)lpParam;
	
	
	Sleep(300);
	pThis->m_pFr->m_pTreeView->lmc1_Mark(FALSE);//mark from memory
	return 0L;
	
}

//DEL void CControlWnd::OnReset() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL //	m_nIsMarkFromFile = FALSE;
//DEL 
//DEL }

void CControlWnd::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(isInsert)
	{
		MessageBox(_T("Insert...please don't close"));
	}
	else
	{
		CFormView::OnClose();
	}
	
}

void CControlWnd::Convert(int mode, int expd, int samples, int index)
{
	int i,j,sign;
	unsigned short words[4];
	static double factors[] = {1.05963812934E-14,1.05963812934E-14,
		1.05963812934E-14,1.24900090270331E-9,1.05963812934E-14,
		8.3819032E-8,.00390625}; /* conversion factors */
	for ( i = 0 ; i < samples ; i++ )
	{
		sign = 0;
		fdata[i+index*samples] = 0.0;
		/* get 8 data bytes ( 4 *2 bytes each ) */
		for ( j = 0 ; j < 4 ; j ++)words[j] = Buffer[ 4*i +j];
		if ((int)words[3] < 0) /* if answer < 0 convert to magnitude and sign */
		{
			sign = 1; /* sign of answer */
			for ( j = 0 ; j < 4 ; j++) words[j] = ~words[j]; /* take 1's complement */
		}
		/* convert to floating point */
		for ( j = 0 ; j < 4 ; j++)fdata[i+index*samples] = fdata[i+index*samples]*65536.0 + (double)words[3-j];
		/* if number is negative add 1 to get 2's complement and change sign */
		if (sign)fdata[i+index*samples] = -1.0 * (fdata[i+index*samples] + 1.0);
		/* now multiply by conversion factor */
		fdata[i+index*samples] = factors[mode] * fdata[i+index*samples];
		if (expd) fdata[i+index*samples] = fdata[i+index*samples]*1.0E-3; /* reduce by 1000 if expand is on */
	}

}
double CountDistance(double retime)
{
	const long  CV=299792458;
	double tmpretime;
	
	tmpretime = CV*(retime)/2;
	return tmpretime;
	
} 

double CountAngle(double angle1, double angle2)
{
	double temAngle1 = .0f;
	double temAngle2 = .0f;
	temAngle1 = cosf(temAngle1)*cosf(temAngle1);
	temAngle2 = tanf(temAngle2)*tanf(temAngle2);
	
	return sqrtf(1+temAngle1*temAngle2);
}


void CControlWnd::NormalizeData(double *dx, double *dy, double *dz, int length)
{
	double mediumX=0.0;
	double mediumY =0.0;
	double mediumZ = 0.0;
	double tmpTotalX = .0f;
	double tmpTotalY = .0f;
	double tmpTotalZ = .0f;
	int i=0;
	for (;i<length;++i)
	{
		tmpTotalX+=dx[i];
		tmpTotalY += dy[i];
		tmpTotalZ += dz[i];
	}
	mediumX = tmpTotalX/length;
	mediumY = tmpTotalY/length;
	mediumZ = tmpTotalZ/length;
	for(i=0;i<length;++i)
	{
		dx[i] = dx[i] - mediumX ;
		dy[i] = dy[i] - mediumY;
		dz[i] = dz[i] - mediumZ;
		
	}
	//使它们到原点的平均距离的平方是1
	double meandis=0;
	for(i=0;i<length;i++)
	{
		meandis+=(float)pow(dx[i]*dx[i]+dy[i]*dy[i]+dz[i]*dz[i],0.5);
	}
	meandis=meandis/length;
	for(i=0;i<length;i++)
	{
		dx[i]=dx[i]/meandis;
		dy[i]=dy[i]/meandis;
		dz[i]=dz[i]/meandis;
	}




}

void CControlWnd::ReCountFromDb(double *angleH, double *angleV, double *Dist, int length)
{
	CDemoDoc *pDoc = m_pCon->GetDocument();
	for (int j = 0;j<MEASURETIMES;++j)
	{
		pDoc->DataX[j] = .0f;
		pDoc->DataY[j] = .0f;
		pDoc->DataZ[j] = .0f;
	}
	double tmpX = .0f;
	double tmpY = .0f;
	double tmpZ = .0f;
	int i = 0;
	for (;i<length;++i)
	{
		tmpX = Dist[i]*sinf(angleH[i])/CountAngle(angleH[i],angleV[i]);
		
		//	DataX[u] = tmpX;
		pDoc->DataX[i] = tmpX;
		tmpY = Dist[i]*cosf(angleH[i])*tanf(angleV[i])/CountAngle(angleH[i],angleV[i]);
		
		//	DataY[i] = tmpY;
		pDoc->DataY[i] = tmpY;
		tmpZ = Dist[i]*cosf(angleH[i])/CountAngle(angleH[i],angleV[i]);
		
		//DataZ[i] = tmpZ;
		pDoc->DataZ[i] = tmpZ;
		


	}
	NormalizeData(pDoc->DataX,pDoc->DataY,pDoc->DataZ,m_nDrawCounter);


	
}
