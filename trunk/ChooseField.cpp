// ChooseField.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ChooseField.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseField dialog
extern CDemoApp theApp;

CChooseField::CChooseField(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseField::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseField)
		// NOTE: the ClassWizard will add member initialization here
	m_nReturnField = _T("");
	m_pRecord = NULL;

	//}}AFX_DATA_INIT
}


void CChooseField::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseField)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_FIELD,m_nAllFields);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseField, CDialog)
	//{{AFX_MSG_MAP(CChooseField)
	ON_LBN_DBLCLK(IDC_FIELD, OnDblclkField)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_DELETEFROMDB, OnDeletefromdb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseField message handlers

BOOL CChooseField::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	this->ReadFromDataBase();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CChooseField::OnDblclkField() 
{
	// TODO: Add your control notification handler code here
	
}

void CChooseField::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_pRecord->State)
	{
		m_pRecord->Close();
		m_pRecord = NULL;
	}
}

void CChooseField::OnOK() 
{
	// TODO: Add extra validation here
	
	int nSelect = m_nAllFields.GetCurSel();
	CString tmpString;
	m_nAllFields.GetText(nSelect,tmpString);
	m_nReturnField = tmpString;
	UpdateData(TRUE);
	CDialog::OnOK();
}



void CChooseField::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_nAllFields.SetCurSel(0);
	SendMessage(WM_CLOSE,0,0);

	CDialog::OnCancel();
}

void CChooseField::OnDeletefromdb() 
{
	// TODO: Add your control notification handler code here
	int nMessage = MessageBox(_T("数据将从数据库永久删除?"),_T("询问"),4+32+0);
	if (nMessage == IDYES)
	{
		CString deleteField;
		int nSelect = m_nAllFields.GetCurSel();
		m_nAllFields.GetText(nSelect,deleteField);

		m_pRecord.CreateInstance(__uuidof(Recordset));
		CString vSQLIN;
		CString strFor;
		CString tmpfield;
		_variant_t vFileValue;
		
		strFor.Format(_T("delete from datatable where DATANAME='%s'"),deleteField);
		theApp.m_pConnection->BeginTrans();
		try
		{
			m_pRecord = theApp.m_pConnection->Execute(_bstr_t(strFor),NULL,adCmdText);
		}
		catch (_com_error* e)
		{
			AfxMessageBox(e->ErrorMessage());
		}
		theApp.m_pConnection->CommitTrans();
		MessageBox(_T("数据已经删除完毕"),_T("提示"),0+64+0);

	}
	UpdateData(FALSE);


}

void CChooseField::ReadFromDataBase()
{
	m_pRecord.CreateInstance(__uuidof(Recordset));
	CString vSQLIN;
	CString strFor;
	CString tmpfield;
	_variant_t vFileValue;
	
	strFor.Format(_T("select distinct DATANAME from datatable"));
	m_pRecord = theApp.m_pConnection->Execute(_bstr_t(strFor),NULL,adCmdText);
	if((m_pRecord->BOF) && (m_pRecord->adoEOF))
	{
		MessageBox(_T("数据库中没有任何启示!将返回空值"),_T("提示"),0+48);
		m_nReturnField = _T("");
		SendMessage(WM_CLOSE,0,0);
		
	}
	else
	{
		while (VARIANT_FALSE == m_pRecord->adoEOF)
		{
			vFileValue = m_pRecord->GetCollect("DATANAME");
			tmpfield = (LPSTR)_bstr_t(vFileValue);
			m_nAllFields.AddString(tmpfield);
			tmpfield = _T("");
			m_pRecord->MoveNext();
			
		}
		
		
		
	}
	m_pRecord->Close();
	m_nAllFields.SetCurSel(0);


}
