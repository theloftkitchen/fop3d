// DemoEzdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoEzd.h"
#include "DemoEzdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoEzdDlg dialog

CDemoEzdDlg::CDemoEzdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoEzdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoEzdDlg)
	m_strFileName = _T("");
	m_strEntName = _T("");
	m_strText = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hEzdDLL = NULL;
	lmc1_Initial = NULL;
	lmc1_Close = NULL;
	lmc1_LoadEzdFile = NULL;
	lmc1_Mark = NULL;
	lmc1_MarkEntity= NULL;
	lmc1_GetPrevBitmap = NULL;
	lmc1_ReadPort = NULL;
	lmc1_WritePort = NULL;
	
	lmc1_SetDevCfg= NULL;
	lmc1_SetHatchParam= NULL;
	lmc1_SetFontParam= NULL;
	lmc1_GetPenParam= NULL;
	lmc1_SetPenParam= NULL;
	lmc1_ClearEntLib= NULL;
	lmc1_AddTextToLib= NULL;
	lmc1_AddFileToLib= NULL;
	lmc1_AddBarCodeToLib= NULL;
	lmc1_ChangeTextByName= NULL;

	lmc1_AxisMoveTo=NULL;
	lmc1_AxisCorrectOrigin=NULL;
	lmc1_GetAxisCoor=NULL;
	lmc1_SaveEntLibToFile=NULL;
	m_pPrevBmp = NULL;
}

void CDemoEzdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoEzdDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strFileName);
	DDX_Text(pDX, IDC_EDIT_ENTNAME, m_strEntName);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_strText);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoEzdDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoEzdDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_RUNENT, OnButtonRunent)
	ON_BN_CLICKED(IDC_BUTTON_ADDTEXT, OnButtonAddtext)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoEzdDlg message handlers
void CDemoEzdDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_pPrevBmp != NULL)
	{
		delete m_pPrevBmp;
		m_pPrevBmp = NULL;
	}

	if(lmc1_Close!=NULL)
	{
		lmc1_Close();
	}
	
	if(m_hEzdDLL != NULL)
	{
		FreeLibrary(m_hEzdDLL);//释放DLL句柄
		m_hEzdDLL = NULL;
	}
}

BOOL CDemoEzdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	

	m_hEzdDLL = LoadLibrary(_T("MarkEzd.dll"));//加载动态连接库	
	if(m_hEzdDLL==NULL)
	{
		AfxMessageBox(_T("Can not find MarkEzd.dll!"));		
	}
	else
	{
		lmc1_Initial=(LMC1_INITIAL)GetProcAddress(m_hEzdDLL,"lmc1_Initial");
		if(lmc1_Initial==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_Initial in MarkEzd.dll!"));	
		}

		lmc1_Close=(LMC1_CLOSE)GetProcAddress(m_hEzdDLL,"lmc1_Close");
		if(lmc1_Close==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_Close in MarkEzd.dll!"));	
		}

		lmc1_LoadEzdFile=(LMC1_LOADEZDFILE)GetProcAddress(m_hEzdDLL,"lmc1_LoadEzdFile");
		if(lmc1_LoadEzdFile==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_LoadEzdFile in MarkEzd.dll!"));	
		}

		lmc1_Mark=(LMC1_MARK)GetProcAddress(m_hEzdDLL,"lmc1_Mark");
		if(lmc1_Mark==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_Mark in MarkEzd.dll!"));	
		}

		lmc1_MarkEntity=(LMC1_MARKENTITY)GetProcAddress(m_hEzdDLL,"lmc1_MarkEntity");
		if(lmc1_MarkEntity==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_MarkEntity in MarkEzd.dll!"));	
		}

		lmc1_GetPrevBitmap=(LMC1_GETPREVBITMAP)GetProcAddress(m_hEzdDLL,"lmc1_GetPrevBitmap");
		if(lmc1_GetPrevBitmap==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_GetPrevBitmap in MarkEzd.dll!"));	
		}

		lmc1_ReadPort=(LMC1_READPORT)GetProcAddress(m_hEzdDLL,"lmc1_ReadPort");
		if(lmc1_ReadPort==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_ReadPort in MarkEzd.dll!"));	
		}

		lmc1_WritePort=(LMC1_WRITEPORT)GetProcAddress(m_hEzdDLL,"lmc1_WritePort");
		if(lmc1_WritePort==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_WritePort in MarkEzd.dll!"));	
		}

		lmc1_SetDevCfg=(LMC1_SETDEVCFG)GetProcAddress(m_hEzdDLL,"lmc1_SetDevCfg");
		if(lmc1_SetDevCfg==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetDevCfg in MarkEzd.dll!"));	
		}
		lmc1_SetHatchParam=(LMC1_SETHATCHPARAM)GetProcAddress(m_hEzdDLL,"lmc1_SetHatchParam");
		if(lmc1_SetHatchParam==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetHatchParam in MarkEzd.dll!"));	
		}
		lmc1_SetFontParam=(LMC1_SETFONTPARAM)GetProcAddress(m_hEzdDLL,"lmc1_SetFontParam");
		if(lmc1_SetFontParam==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetFontParam in MarkEzd.dll!"));	
		}
		lmc1_GetPenParam=(LMC1_GETPENPARAM)GetProcAddress(m_hEzdDLL,"lmc1_GetPenParam");
		if(lmc1_GetPenParam==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_GetPenParam in MarkEzd.dll!"));	
		}
		lmc1_SetPenParam=(LMC1_SETPENPARAM)GetProcAddress(m_hEzdDLL,"lmc1_SetPenParam");
		if(lmc1_SetPenParam==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SetPenParam in MarkEzd.dll!"));	
		}

		lmc1_ClearEntLib=(LMC1_CLEARENTLIB)GetProcAddress(m_hEzdDLL,"lmc1_ClearEntLib");
		if(lmc1_ClearEntLib==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_ClearEntLib in MarkEzd.dll!"));	
		}
		lmc1_AddTextToLib=(LMC1_ADDTEXTTOLIB)GetProcAddress(m_hEzdDLL,"lmc1_AddTextToLib");
		if(lmc1_AddTextToLib==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AddTextToLib in MarkEzd.dll!"));	
		}

		lmc1_AddFileToLib=(LMC1_ADDFILETOLIB)GetProcAddress(m_hEzdDLL,"lmc1_AddFileToLib");
		if(lmc1_AddFileToLib==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AddFileToLib in MarkEzd.dll!"));	
		}

		lmc1_AddBarCodeToLib=(LMC1_ADDBARCODETOLIB)GetProcAddress(m_hEzdDLL,"lmc1_AddBarCodeToLib");
		if(lmc1_AddBarCodeToLib==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AddBarCodeToLib in MarkEzd.dll!"));	
		}

		lmc1_ChangeTextByName=(LMC1_CHANGETEXTBYNAME)GetProcAddress(m_hEzdDLL,"lmc1_ChangeTextByName");
		if(lmc1_ChangeTextByName==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_ChangeTextByName in MarkEzd.dll!"));	
		}		


		lmc1_AxisMoveTo=(LMC1_AXISMOVETO)GetProcAddress(m_hEzdDLL,"lmc1_AxisMoveTo");
		if(lmc1_AxisMoveTo==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AxisMoveTo in MarkEzd.dll!"));	
		}		
		lmc1_AxisCorrectOrigin=(LMC1_AXISCORRECTORIGIN)GetProcAddress(m_hEzdDLL,"lmc1_AxisCorrectOrigin");
		if(lmc1_AxisCorrectOrigin==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_AxisCorrectOrigin in MarkEzd.dll!"));	
		}		
		lmc1_GetAxisCoor=(LMC1_GETAXISCOOR)GetProcAddress(m_hEzdDLL,"lmc1_GetAxisCoor");
		if(lmc1_GetAxisCoor==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_GetAxisCoor in MarkEzd.dll!"));	
		}		

		lmc1_SaveEntLibToFile=(LMC1_SAVEENTLIBTOFILE)GetProcAddress(m_hEzdDLL,"lmc1_SaveEntLibToFile");
		if(lmc1_SaveEntLibToFile==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_SaveEntLibToFile in MarkEzd.dll!"));	
		}		
		
	}
	
	TCHAR path[_MAX_PATH];
    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];        
	GetModuleFileName(::AfxGetApp()->m_hInstance,path,_MAX_PATH);
    _wsplitpath(path,drive,dir,fname,ext);
 
	TCHAR strEzCadPath[256];

	_tcscpy(strEzCadPath,drive);
	_tcscat(strEzCadPath,dir);

	BOOL bTestMode = FALSE;

	int nErr=LMC1_ERR_SUCCESS;
	if(lmc1_Initial!=NULL)
	{
		nErr = lmc1_Initial(strEzCadPath,bTestMode,GetSafeHwnd());
		if(nErr!=LMC1_ERR_SUCCESS)
		{
			CString strErr;
			strErr.Format(_T("Initial lmc1 failed! ErrCode = %d"),nErr);
			AfxMessageBox(strErr);				
		}	
	}


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoEzdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoEzdDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		OnDrawPreview();
	}
}


void CDemoEzdDlg::OnDrawPreview()
{
   CWnd* pWnd = GetDlgItem(IDC_STATIC_WND);
	if(pWnd==NULL)
		return;    	
//	pWnd = this;
	CRect rect;
    pWnd->GetClientRect(rect);
    rect.InflateRect(-2,-2);
    
	CDC* pDC = pWnd->GetDC(); 
	CRgn pRgn;
	pRgn.CreateRectRgnIndirect(rect);
	pDC->SelectClipRgn(&pRgn);
	
	//CBrush Brsh(GetSysColor(COLOR_BTNFACE));
	CBrush Brsh(RGB(255,255,255));
	pDC->FillRect(rect,&Brsh);	
	if(m_pPrevBmp != NULL)
    {//显示预览图片	
		CDC memDC;
		CBitmap* pOld=NULL;
		memDC.CreateCompatibleDC(pDC);
		
		pOld = memDC.SelectObject(m_pPrevBmp);
		
		BITMAP bm;
		m_pPrevBmp->GetBitmap(&bm);		
		CPoint ptCen = rect.CenterPoint ();
		::SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);	
		
		pDC->BitBlt (ptCen.x - bm.bmWidth/2,ptCen.y - bm.bmHeight/2,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
	
		memDC.SelectObject(pOld);		
	}	
	
	pWnd->ReleaseDC( pDC );     
    return;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoEzdDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoEzdDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}


CString gf_LoadAllLineStr(CString filename)
{	
	CFile file;
	CFileException ex;	
	if(!file.Open(filename, CFile::modeRead | CFile::typeBinary,&ex))
	{		
		return _T("");
	}
	
	int fileLen = file.GetLength();
	int nSizeFile = fileLen;
	
	char* pCharBuf = new char[fileLen+1];
	if(pCharBuf == NULL)
	{
		return _T("");
	}
	
	if(file.Read(pCharBuf,fileLen)!=(UINT)fileLen)
	{
		delete[] pCharBuf;
		pCharBuf = NULL;
		file.Close();
		return _T("");
	}	
	file.Close();
	pCharBuf[fileLen]=0;

	CString strLine;

	fileLen=fileLen/2;
		TCHAR* pTCharBuf = (TCHAR*)pCharBuf;
		for(int i=1;i<fileLen;i++)
		{
			strLine+=pTCharBuf[i];
		}		

	delete[] pCharBuf;
	return strLine;
}
void CDemoEzdDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,_T(""),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("Ezcad file(*.ezd)|*.ezd|"));
	
	if(dlg.DoModal()==IDOK)
	{
		m_strFileName = dlg.GetPathName();
		UpdateData(FALSE);

		if(lmc1_LoadEzdFile==NULL )
		{
			return;
		}
		
		TCHAR szFile[256];
		_tcscpy(szFile,m_strFileName);
		int nErr = lmc1_LoadEzdFile(szFile);
		if(nErr!=LMC1_ERR_SUCCESS)
		{
			AfxMessageBox(_T("Read ezdfile failed!"));				
		}

		if(lmc1_GetPrevBitmap==NULL)
		{
			return;
		}

		if(m_pPrevBmp!=NULL)
		{
			delete m_pPrevBmp;
			m_pPrevBmp = NULL;
		}

		CWnd* pWnd = GetDlgItem(IDC_STATIC_WND);
		if(pWnd==NULL)
			return;    	
		
		CRect rect;
		pWnd->GetClientRect(rect);

		CClientDC previewDC(pWnd);
		int nCaps = previewDC.GetDeviceCaps(BITSPIXEL);
		CDC* pDC = &previewDC;

		m_pPrevBmp = lmc1_GetPrevBitmap(pWnd->GetSafeHwnd(),rect.Width(),rect.Height());
		OnDrawPreview();
	}
}


void CDemoEzdDlg::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(lmc1_Mark==NULL)
	{
		return;
	}
	

	lmc1_Mark(FALSE);
	UpdatePrevBmp();
	AfxMessageBox(_T("Mark file finish!"));	
}

void CDemoEzdDlg::UpdatePrevBmp()
{
	if(m_pPrevBmp!=NULL)
	{
		delete m_pPrevBmp;
		m_pPrevBmp = NULL;
	}
	
	CWnd* pWnd = GetDlgItem(IDC_STATIC_WND);
	if(pWnd==NULL)
		return;    	
	
	CRect rect;
	pWnd->GetClientRect(rect);
	
	CClientDC previewDC(pWnd);
	int nCaps = previewDC.GetDeviceCaps(BITSPIXEL);
	CDC* pDC = &previewDC;
	
	m_pPrevBmp = lmc1_GetPrevBitmap(pWnd->GetSafeHwnd(),rect.Width(),rect.Height());
	OnDrawPreview();
}

void CDemoEzdDlg::OnButtonRunent() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if(lmc1_Mark==NULL)
	{
		return;
	}
	
	TCHAR strName[256];
	_tcscpy(strName,m_strEntName);
	
	lmc1_MarkEntity(strName);
	
	AfxMessageBox(_T("Mark entity finish!"));	
}

void CDemoEzdDlg::OnButtonAddtext() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	TCHAR strText[1000];
	TCHAR strEnt[1000]=_T("TEXT");
	_tcscpy(strText,m_strText);

	lmc1_AddTextToLib(strText,strEnt,0,0,0,4,0,0,TRUE);
	UpdatePrevBmp();
}





void CDemoEzdDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	if(lmc1_SetDevCfg==NULL)
	{
		return;
	}
	
	lmc1_SetDevCfg();
}

void CDemoEzdDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,_T(""),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("All file(*.*)|*.*|"));
	
	if(dlg.DoModal()==IDOK)
	{
		TCHAR strText[1000];
		TCHAR strEnt[1000]=_T("FILE");
		_tcscpy(strText,dlg.GetPathName());
		lmc1_AddFileToLib(strText,strEnt,0,0,0,0,1,0,FALSE);
		UpdatePrevBmp();
	}
}

void CDemoEzdDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	double dBarWidthScale[4]={1,2,3,4};//条宽比例	(与最窄模块宽相比)
	double dSpaceWidthScale[4]={1,2,3,4};//空宽比例(与最窄模块宽相比)
		TCHAR strEnt[1000]=_T("BARCODE");

	lmc1_AddBarCodeToLib(_T("123456789"),
		strEnt,
		                    0,0,0,0,0,FALSE,
							BARCODETYPE_39,
							BARCODEATTRIB_HUMANREAD,
							10,
							0.3,
							dBarWidthScale,
							dSpaceWidthScale,
							1,
							10,
							10,
							10,
							10,
							10,
							3,
							3,
							0,
							DATAMTX_SIZEMODE_SMALLEST,
							2,
							1,
							0,
							0,
							0,
							0.5,
							_T("Arial"));

	UpdatePrevBmp();
}
