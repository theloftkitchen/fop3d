#if !defined(AFX_SELECTDLG_H__C37B9FEB_F914_427F_96B7_45D6D8924651__INCLUDED_)
#define AFX_SELECTDLG_H__C37B9FEB_F914_427F_96B7_45D6D8924651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDLG.h : header file
//
#include "gl\gl.h"
#include "gl\glu.h"
#include "rDib.h"

#define MAXPOINT 1000000 //最多允许显示的点数

/////////////////////////////////////////////////////////////////////////////
// SelectDLG dialog

class SelectDLG : public CDialog
{
// Construction
public:
	float m_point3d[MAXPOINT][3];//三维点坐标矩阵
	float m_point2d[MAXPOINT][2];//二维匹配点坐标矩阵
	float m_point3d_old[MAXPOINT][3];//存放三维点坐标原始数据
	float m_point2d_old[MAXPOINT][2];//存放二维匹配点坐标原始数据
	long n3dpoint;//三维点个数
	long n2dpoint;//二维点个数
	int ntri;//三角个数
	int **triangle;//三角顶点索引
	int tritemp[MAXPOINT][3];
	DIB mDib,mDib2;
	CSize ImageSize;
	void triangulation(float m_p2D[MAXPOINT][2],int numberofcorner,int vertexindex[MAXPOINT*10],int& numberoftriangle);

	SelectDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectDLG)
	enum { IDD = IDD_SELECTDLG };
	CString	m_2dpos;
	CString	m_3dpos;
	CString	m_texpos;
	CString	m_tripos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelectDLG)
	afx_msg void OnLoad2d();
	afx_msg void OnLoad3d();
	afx_msg void OnLoadtex();
	afx_msg void OnLoadtri();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDLG_H__C37B9FEB_F914_427F_96B7_45D6D8924651__INCLUDED_)
