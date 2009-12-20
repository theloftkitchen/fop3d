                 // demoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include <math.h>
#include "demo.h"

#include "demoDoc.h"
#include "demoView.h"
#include "SelectDLG.h"
#include "triangle.h"
#include "ControlWnd.h"

//#include "AxisTransform.h"
#include <vector>
#include <algorithm>
using namespace std;


 




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  pai 3.1415926


//global variable

extern vector<double>DataX;
extern vector<double>DataY;
extern vector<double>DataZ;

//Arcball
ArcBallT ArcBall(640.0f, 480.0f);
Matrix4fT Transform={1.0f,0.0f,0.0f,0.0f,// NEW: Final Transform
						 0.0f,1.0f,0.0f,0.0f,
						 0.0f,0.0f,1.0f,0.0f,
						 0.0f,0.0f,0.0f,1.0f};
Matrix3fT LastRot  ={1.0f,0.0f,0.0f,	// NEW: Last Rotation
						 0.0f,1.0f,0.0f,
						 0.0f,0.0f,1.0f};
Matrix3fT ThisRot  ={1.0f,0.0f,0.0f,	// NEW: This Rotation
						 0.0f,1.0f,0.0f,
						 0.0f,0.0f,1.0f};

//add some global variables:

GLfloat mat_ambient[]= { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat mat_shininess[] = { 50.0f };

GLfloat light_diffuse[]= { 0.0, 1.0, 0.0, 1.0};
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };






/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CView)

BEGIN_MESSAGE_MAP(CDemoView, CView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_LOAD, OnLoad)
	ON_COMMAND(IDM_SHOW_POINTS, OnShowPoints)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_SHOW_MESH, OnShowMesh)
	ON_COMMAND(IDM_TEXTURE_MAPPING, OnTextureMapping)
	ON_COMMAND(ID_XYSHIFT, OnXyshift)
	ON_COMMAND(ID_XYROTATE, OnXyrotate)
	ON_COMMAND(ID_ZROTATE, OnZrotate)
	ON_COMMAND(ID_RESETCAM, OnResetcam)
	ON_COMMAND(ID_ANIMATE, OnAnimate)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(IDM_SHOW_POINTS, OnUpdateShowPoints)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_MESH, OnUpdateShowMesh)
	ON_UPDATE_COMMAND_UI(IDM_TEXTURE_MAPPING, OnUpdateTextureMapping)
	ON_UPDATE_COMMAND_UI(ID_ANIMATE, OnUpdateAnimate)
	ON_UPDATE_COMMAND_UI(ID_XYROTATE, OnUpdateXyrotate)
	ON_UPDATE_COMMAND_UI(ID_ZROTATE, OnUpdateZrotate)
	ON_UPDATE_COMMAND_UI(ID_XYSHIFT, OnUpdateXyshift)
	ON_COMMAND(ID_SHOWBACK, OnShowback)
	ON_UPDATE_COMMAND_UI(ID_SHOWBACK, OnUpdateShowback)
	ON_COMMAND(ID_SHOWINDEX, OnShowindex)
	ON_UPDATE_COMMAND_UI(ID_SHOWINDEX, OnUpdateShowindex)
	ON_COMMAND(ID_LIGHT, OnLight)
	ON_UPDATE_COMMAND_UI(ID_LIGHT, OnUpdateLight)
	ON_COMMAND(ID_ENABLESELECT, OnEnableselect)
	ON_UPDATE_COMMAND_UI(ID_ENABLESELECT, OnUpdateEnableselect)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_SAVERESULT, OnSaveresult)
	ON_COMMAND(ID_BACKWARD, OnBackward)
	ON_COMMAND(ID_SAVETRINDEX, OnSavetrindex)
	ON_COMMAND(ID_SHOWAXIS, OnShowaxis)
	ON_UPDATE_COMMAND_UI(ID_SHOWAXIS, OnUpdateShowaxis)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here
	m_pDC=NULL;
	LButtonSta=FALSE;
	RButtonSta=FALSE;
	rot[0]=0;
	rot[1]=0;
	rot[2]=0;
	zoom=-4.5f;
	xyshift[0]=0;
	xyshift[1]=0;
	selectindex=-1;
	nindeleteindex=0;
	TEXTURE=FALSE;
	SHOWPOINTS=TRUE;
	SHOWTRIMESH=FALSE;
	ENABLELIGHT=FALSE;
	ENABLEXYROTATE=TRUE;
	ENABLEZROTATE=FALSE;
	ENABLEXYSHIFT=FALSE;
	ENABLEANIMATE=FALSE;
	SHOWBACK=FALSE;
	SHOWAXIS=FALSE;
	SHOWINDEX=FALSE;
	ENABLESELECT=FALSE;
	CURSORINWND=TRUE;
	CTRLKEYDOWN=FALSE;
	m_timer=0;

	dlgload.n3dpoint=0;
	dlgload.n2dpoint=0;
	dlgload.ntri=0;
	

	//Arcball
	isClicked=false;
	isRClicked=false;
	isDragging=false;
	//angle of rotating;
	m_RotateAngle = 0;

	//variable initiation of axis rotating
	m_fRotateX = 1.0f;
	m_fRotateY = 1.0f;
	m_fRotateZ = 1.0f;


	lmc1_Initial = NULL;
	lmc1_LoadEzdFile = NULL;
	lmc1_Close = NULL;
	lmc1_MarkEntity = NULL;
	lmc1_ReadPort = NULL;
	lmc1_WritePort = NULL;
	lmc1_GetPrevBitmap = NULL;
	lmc1_SetDevCfg = NULL;
	lmc1_Mark = NULL;

	

}

CDemoView::~CDemoView()
{
	//delete dlgload.triangle;
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	DrawScene(GL_RENDER);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView printing

BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

int CDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	Init();
	
	


//	this->Count3DAxis(timeAr,15600);

	

	return 0;
}

void CDemoView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	if (lmc1_Close != NULL)
	{
		lmc1_Close();
		
	}
	if (m_hEzdDLL !=NULL)
	{
		FreeLibrary(m_hEzdDLL);
		m_hEzdDLL = NULL;
		}
	HGLRC hrc;
	hrc=::wglGetCurrentContext();   //得到当前RC句柄
	::wglMakeCurrent(NULL,NULL);    //使当前RC无效

	if(hrc)
		::wglDeleteContext(hrc);    //删除当前RC

	if(m_pDC)
		delete m_pDC;               //删除当前DC			
}

void CDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(cy>0)
	{
		if((m_oldRect.right>cx)|(m_oldRect.bottom>cy))
		RedrawWindow();

		m_oldRect.right=cx;
		m_oldRect.bottom=cy;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,(GLdouble)cx/(GLdouble)cy,0.1,1000.0);
		glViewport(0,0,cx,cy);

		ArcBall.setBounds(cx,cy);
	}
	Invalidate();		
}

void CDemoView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	HGLRC hrc;

	m_pDC=new CClientDC(this);//得到当前窗口DC

	ASSERT(m_pDC!=NULL);      //诊断信息

    //设置象素格式
	if(!bSetupPixelFormat()) return;

    //测试象素格式
	n=::GetPixelFormat(m_pDC->GetSafeHdc());//得到当前DC象素格式索引
	::DescribePixelFormat(m_pDC->GetSafeHdc(),n,sizeof(pfd),&pfd);//设置象素格式

    //创建与当前DC兼容的RC
	hrc=wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(),hrc);//使RC当前化

	GetClientRect(&m_oldRect);

	//创建光源
  /*
	GLfloat light_position0[]={0.0f,0.0f,-9.0f,0.0f};
    GLfloat light_position1[]={0.0f,0.0f,9.0f,0.0f};
	GLfloat light_diffuse[]={1.0f,1.0f,1.0f,0.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position0);
	glLightfv(GL_LIGHT1,GL_POSITION,light_position1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,light_diffuse);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);//启动双面光照(important!)
	*/
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	
}

BOOL CDemoView::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd=          //初始化象素格式结构体
	{
		sizeof(PIXELFORMATDESCRIPTOR),         //size of this pdf
		1,                                     //version number
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, ////support window & opengl
		PFD_TYPE_RGBA,                         //RGBA type
		24,                                    //24-bit color depth
		0,0,0,0,0,0,                           //colot bits ignored
		0,                                     //no alpha buffer
		0,                                     //shift bit ignored
		0,                                     //no accumulation buffer
		0,0,0,0,                               //accum bits ignored
		32,                                    //32-bits z-buffer
		0,                                     //no stencil buffer
		0,                                     //no auxiliary buffer
		PFD_MAIN_PLANE,                        //main layer
		0,                                     //reserved
		0,0,0                                  //layer masks ignored
	};
	int pixelformat;
    //从当前DC支持的象素格式中选择与pfd所指定最匹配一个，返回其索引
	if((pixelformat=ChoosePixelFormat(m_pDC->GetSafeHdc(),&pfd))==0)
	{
		MessageBox(_T("ChoosePixelFormat failed"));
		return FALSE;
	}
    //把指定DC象素格式设置成由索引指向的象素格式
	if(SetPixelFormat(m_pDC->GetSafeHdc(),pixelformat,&pfd)==FALSE)
	{
		MessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}

	return TRUE;
}

void CDemoView::DrawScene(GLenum mode)
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	if(ENABLELIGHT==TRUE)//启用光照
		{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);//启动双面光照(important!)
		}
	else
		glDisable(GL_LIGHTING);
	

	if(SHOWBACK==TRUE)//背面不可见
	{
		glFrontFace(GL_CW);//顺时针为正
		glPolygonMode(GL_BACK,GL_LINE);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);
	}
	else
	{
		glPolygonMode(GL_BACK,GL_FILL);
		//glCullFace(GL_FALSE);
		//glDisable(GL_CULL_FACE);
	}

	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xyshift[0],xyshift[1],zoom);//平移

	//Arcball rotate control
	glPushMatrix();
	glMultMatrixf(Transform.M);//旋转
	
	//自由旋转
	if(ENABLEANIMATE)
	{
		float x,y,z;
		x=rot[0]*3.1416/180;
		y=rot[1]*3.1416/180;
		z=rot[2]*3.1416/180;
		glRotatef(rot[0], 0.0f, 1.0f,0.0f);//X
		glRotatef(rot[1], 1.0f, 0.0f, 0.0f);//Y
		glRotatef(rot[2], 0.0f, 0.0f, 1.0f);//Z
	}
	glRotatef(m_fRotateX,1,0,0);
	glRotatef(m_fRotateY,0,1,0);
	glRotatef(m_fRotateZ,0,0,1);

	if(SHOWPOINTS==TRUE)
	{
		
		DrawPoints(mode);
	}
    if(SHOWTRIMESH==TRUE)
		DrawTriMesh(mode);
	if(ENABLELIGHT==TRUE)
		ShowLight();
    if(TEXTURE==TRUE)
	    GlTexture();//贴纹理

	if(SHOWAXIS==TRUE)
		DrawAxis();
	if(SHOWINDEX==TRUE)
		DrawIndex();
	
	glPopMatrix();
	glFlush();
	SwapBuffers(wglGetCurrentDC());

	//在状态栏显示旋转角度
	CMainFrame* pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	CStatusBar* PStatus=&pFrame->m_wndStatusBar;
	CString statusmessage;
	GLint  angle=.0;
	if(ENABLEANIMATE)
	statusmessage.Format(_T("X: %d ;Y: %d ;Z: %d"),(int)rot[0]%(360),(int)rot[1]%(360),(int)rot[2]%(360));
	else
	{
		angle= (int)((180*m_RotateAngle)/pai)%360;
		statusmessage.Format(_T("the angle is :%d"),angle);

	}

//	statusmessage.Format("X: %f ;Y: %f ;Z: %f",positionx,positiony,positionz);
//	statusmessage.Format("X: %f ;Y: %f ;Z: %d",rot[0],rot[1],rot[2]);
//	PStatus->SetPaneText(1,statusmessage);
	if(ENABLEANIMATE)
		statusmessage.Format(_T("X: %d ;Y: %d ;Z: %d"),(int)rot[0]%(360),(int)rot[1]%(360),(int)rot[2]%(360));
	else
	{
		angle= (int)((180*m_RotateAngle)/pai)%360;
		statusmessage.Format(_T("the angle is :%d"),angle);
		
	}
	
	this->m_pFr->m_pCtrlWnd->GetDlgItem(IDC_SHOWANGLE)->SetWindowText(statusmessage);








	

}

//显示函数//////////////////////////////////////////////////////////////////
//显示点集
void CDemoView::DrawPoints(GLenum mode)
{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		if(mode!=GL_SELECT)
		{
			//	glPointSize(2.0f);
			glBegin(GL_POINTS);
			{
			/*
			for(int i=1;i<=dlgload.n3dpoint;i++)
			{
			//if(mode==GL_SELECT) glLoadName(i);
			if(i==(int)selectindex)
			{
			glColor3f(0.0f,0.0f,1.0f);
			//	glVertex3f(dlgload.m_point3d[i-1][0],dlgload.m_point3d[i-1][1],dlgload.m_point3d[i-1][2]);
			glVertex3f(dlgload.m_point3d[i][0],dlgload.m_point3d[i][1],dlgload.m_point3d[i][2]);
			//	glVertex3f(dlgload.m_point3d[i+1][0],dlgload.m_point3d[i+1][1],dlgload.m_point3d[i+1][2]);
			}
			else
			{
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(dlgload.m_point3d[i][0],dlgload.m_point3d[i][1],dlgload.m_point3d[i][2]);
			
			  }
			}*/
				
				
				
				
				
			
			for(int i=0;i < this->m_pFr->m_pCtrlWnd->m_nDrawCounter;++i)
			{
			glColor3f(1.0f,1.0f,1.0f);
			
			  glVertex3f(DataX[i],DataY[i],DataZ[i]);
			  
				}
				
				/*
				for (int i = 0;i<cntrldlg.num3Dpoint;++i)
								{
									glColor3f(1.0f,1.0f,1.0f);
									glVertex3f(cntrldlg.m_n3DPoints[i][0],cntrldlg.m_n3DPoints[i][1],cntrldlg.m_n3DPoints[i][2]);
								}*/
				
				
			}
			glEnd();
		}
		//将点变换为球,因为点不是几何体不能工作在选择模式下
		if(mode==GL_SELECT)
		{
			GLfloat red[]={1.0,0.0,0.0,1.0};
			GLfloat white[]={1.0,1.0,1.0,1.0};
			glPolygonMode(GL_BACK,GL_FILL);
			glEnable(GL_LIGHTING);
			for(int i=0;i<dlgload.n3dpoint;i++)
			{
				if(mode==GL_SELECT) glLoadName(i);
				if(i==(int)selectindex)
				{
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,red);
					glTranslatef(dlgload.m_point3d[i][0],dlgload.m_point3d[i][1],dlgload.m_point3d[i][2]);
					glutSolidSphere(0.03,5,5);
					glTranslatef(-dlgload.m_point3d[i][0],-dlgload.m_point3d[i][1],-dlgload.m_point3d[i][2]);
				}
				else
				{
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,white);
					glTranslatef(dlgload.m_point3d[i][0],dlgload.m_point3d[i][1],dlgload.m_point3d[i][2]);
					glutSolidSphere(0.03,5,5);
					glTranslatef(-dlgload.m_point3d[i][0],-dlgload.m_point3d[i][1],-dlgload.m_point3d[i][2]);
				}
			}
			glDisable(GL_LIGHTING);
		}
		glDisable(GL_DEPTH_TEST);
}
//显示三角网格
void CDemoView::DrawTriMesh(GLenum mode)
{
	glLineWidth(1.0f);
    glColor3f(0.0f,0.0f,0.0f);
	for(int i=0;i<dlgload.ntri;i++)
	{
		glBegin(GL_LINE_LOOP);
	        glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][0]][0],(float)dlgload.m_point3d[dlgload.triangle[i][0]][1],(float)dlgload.m_point3d[dlgload.triangle[i][0]][2]);
		    glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][1]][0],(float)dlgload.m_point3d[dlgload.triangle[i][1]][1],(float)dlgload.m_point3d[dlgload.triangle[i][1]][2]);
		    glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][2]][0],(float)dlgload.m_point3d[dlgload.triangle[i][2]][1],(float)dlgload.m_point3d[dlgload.triangle[i][2]][2]);
		glEnd();
	}
}
//显示三角化贴纹理
void CDemoView::GlTexture()
{
	glPushMatrix();
	GLubyte *pTextureBits2=(GLubyte *)dlgload.mDib2.Buffer();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	//定义纹理
	glTexImage2D(GL_TEXTURE_2D,0,3,512,512,0,GL_BGR_EXT,GL_UNSIGNED_BYTE,pTextureBits2);

	//控制纹理
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	//说明纹理贴图方式
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	//启动纹理贴图
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	//定义纹理坐标和物体几何坐标//三角化贴纹理
	for(int i=0;i<dlgload.ntri;i++)
	{
		float texcoord[3][2];
		texcoord[0][0]=(float)dlgload.m_point2d[dlgload.triangle[i][0]][0]/dlgload.ImageSize.cx;
		texcoord[0][1]=(dlgload.ImageSize.cy-(float)dlgload.m_point2d[dlgload.triangle[i][0]][1])/dlgload.ImageSize.cy;
		texcoord[1][0]=(float)dlgload.m_point2d[dlgload.triangle[i][1]][0]/dlgload.ImageSize.cx;
		texcoord[1][1]=(dlgload.ImageSize.cy-(float)dlgload.m_point2d[dlgload.triangle[i][1]][1])/dlgload.ImageSize.cy;
		texcoord[2][0]=(float)dlgload.m_point2d[dlgload.triangle[i][2]][0]/dlgload.ImageSize.cx;
		texcoord[2][1]=(dlgload.ImageSize.cy-(float)dlgload.m_point2d[dlgload.triangle[i][2]][1])/dlgload.ImageSize.cy;
	    glBegin(GL_TRIANGLES);
 		    glTexCoord2f(texcoord[0][0],texcoord[0][1]);
			glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][0]][0],(float)dlgload.m_point3d[dlgload.triangle[i][0]][1],(float)dlgload.m_point3d[dlgload.triangle[i][0]][2]);
 		    glTexCoord2f(texcoord[1][0],texcoord[1][1]);
			glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][1]][0],(float)dlgload.m_point3d[dlgload.triangle[i][1]][1],(float)dlgload.m_point3d[dlgload.triangle[i][1]][2]);
 		    glTexCoord2f(texcoord[2][0],texcoord[2][1]);
			glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][2]][0],(float)dlgload.m_point3d[dlgload.triangle[i][2]][1],(float)dlgload.m_point3d[dlgload.triangle[i][2]][2]);
	    glEnd();
	}
    glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
//启用光照
void CDemoView::ShowLight()
{
	glPushMatrix();

	//定义材质
	GLfloat mat_diffuse[]={0.8f,0.8f,0.5f,1.0f};
    //GLfloat mat_specular[]={0.0f,0.0f,0.0f,1.0f};
    //GLfloat mat_shininess[]={50.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    //glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_SMOOTH);

    glPolygonMode(GL_FRONT,GL_FILL);
	glColor3f(1.0f,1.0f,1.0f);

	for(int i=0;i<dlgload.ntri;i++)
	{
		double dPoint1[3],dPoint2[3],dPoint3[3],dNormal[3];
		dPoint1[0]=dlgload.m_point3d[dlgload.triangle[i][0]][0];
		dPoint1[1]=dlgload.m_point3d[dlgload.triangle[i][0]][1];
		dPoint1[2]=dlgload.m_point3d[dlgload.triangle[i][0]][2];
		dPoint2[0]=dlgload.m_point3d[dlgload.triangle[i][1]][0];
		dPoint2[1]=dlgload.m_point3d[dlgload.triangle[i][1]][1];
		dPoint2[2]=dlgload.m_point3d[dlgload.triangle[i][1]][2];
		dPoint3[0]=dlgload.m_point3d[dlgload.triangle[i][2]][0];
		dPoint3[1]=dlgload.m_point3d[dlgload.triangle[i][2]][1];
		dPoint3[2]=dlgload.m_point3d[dlgload.triangle[i][2]][2];
		CaculateNormal(dPoint1,dPoint2,dPoint3,dNormal);
		glBegin(GL_POLYGON);
			glNormal3dv(dNormal);
			glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][0]][0],(float)dlgload.m_point3d[dlgload.triangle[i][0]][1],(float)dlgload.m_point3d[dlgload.triangle[i][0]][2]);
			glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][1]][0],(float)dlgload.m_point3d[dlgload.triangle[i][1]][1],(float)dlgload.m_point3d[dlgload.triangle[i][1]][2]);
			glVertex3f((float)dlgload.m_point3d[dlgload.triangle[i][2]][0],(float)dlgload.m_point3d[dlgload.triangle[i][2]][1],(float)dlgload.m_point3d[dlgload.triangle[i][2]][2]);
		glEnd();
	}
	glPopMatrix();
}
//显示坐标轴
void CDemoView::DrawAxis()
{
	glPushMatrix();
	glEnable(GL_LINE_SMOOTH);

	glLineWidth(1.0f);
	glBegin(GL_LINES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-1.0f,0.0f,0.0f);
		glVertex3f(1.0f,0.0f,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,-1.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);
	glEnd();
	glBegin(GL_LINES);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f,0.0f,-1.0f);
		glVertex3f(0.0f,0.0f,1.0f);
	glEnd();
	glDisable(GL_LINE_SMOOTH);

	glBegin(GL_TRIANGLES);
	
	//	x arrow
	glColor3f(1,0,0);
	glVertex3f(1, 0, 0);
	glVertex3f(1-0.2, 0.05, 0);
	glVertex3f(1-0.2, -0.05, 0);
	
	glVertex3f(1, 0, 0);
	glVertex3f(1-0.2, 0, 0.05);
	glVertex3f(1-0.2, 0, -0.05);
	
	// y arrow
	glColor3f(0,1,0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1-0.2, 0.05);
	glVertex3f(0, 1-0.2, -0.05);
	
	glVertex3f(0, 1, 0);
	glVertex3f(0.05, 1-0.2, 0);
	glVertex3f(-0.05, 1-0.2, 0);
	
	// z arrow
	glColor3f(0,0,1);
	glVertex3f(0, 0, 1);
	glVertex3f(0.05, 0, 1-0.2);
	glVertex3f(-0.05, 0, 1-0.2);
	
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0.05, 1-0.2);
	glVertex3f(0, -0.05, 1-0.2);
	
	
	glEnd();
	
	glPopMatrix();
	//draw text

	glPushMatrix();

	
	wglUseFontBitmaps(wglGetCurrentDC(),0,256,1000);
	glListBase(1000);

	glColor3f(1.0f,.0f,0.0f);
	glRasterPos3f(1.0f,0.0f,0.0f);
	glCallLists(1,GL_UNSIGNED_BYTE,"X");

	glColor3f(0.0f,1.0f,0.0f);
	glRasterPos3f(0.0f,1.0f,0.0f);
	glCallLists(1,GL_UNSIGNED_BYTE,"Y");

	glColor3f(.0f,0.0f,1.0f);
	glRasterPos3f(0.0f,0.0f,1.0f);
	glCallLists(1,GL_UNSIGNED_BYTE,"Z");
	
	

	glPopMatrix();
	glFlush();
}
//显示索引
void CDemoView::DrawIndex()
{
	glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
	wglUseFontBitmaps(wglGetCurrentDC(),0,256,1000);
	glListBase(1000);

	for(int i=0;i<dlgload.n3dpoint;i++)
	{
		CString index;
		index.Format(_T("%4d"),i);
		glRasterPos3f(dlgload.m_point3d[i][0],dlgload.m_point3d[i][1],dlgload.m_point3d[i][2]);
		glCallLists(4,GL_UNSIGNED_BYTE,index);
	}
	glPopMatrix();
}
//控制函数///////////////////////////////////////////////////////////////
void CDemoView::OnLoad() 
{
	// TODO: Add your command handler code here
	//SelectDLG dlgload;
	if(dlgload.DoModal()==IDOK)
	{
	}
}
void CDemoView::OnShowPoints() 
{
	// TODO: Add your command handler code here
	SHOWPOINTS=!SHOWPOINTS;
	TEXTURE=FALSE;
	//SHOWTRIMESH=FALSE;
	ENABLELIGHT=FALSE;
	Invalidate(FALSE);		
}
void CDemoView::OnShowMesh() 
{
	// TODO: Add your command handler code here
	SHOWTRIMESH=!SHOWTRIMESH;
	TEXTURE=FALSE;
	//SHOWPOINTS=FALSE;
	ENABLELIGHT=FALSE;
	Invalidate(FALSE);	
}
void CDemoView::OnTextureMapping() 
{
	// TODO: Add your command handler code here
	TEXTURE=TRUE;
	SHOWPOINTS=FALSE;
	SHOWTRIMESH=FALSE;
	ENABLELIGHT=FALSE;
	Invalidate(FALSE);	
}
void CDemoView::OnLight() 
{
	// TODO: Add your command handler code here
	ENABLELIGHT=TRUE;
	SHOWPOINTS=FALSE;
	TEXTURE=FALSE;
	SHOWTRIMESH=FALSE;
	Invalidate(FALSE);
}
void CDemoView::OnXyrotate() 
{
	// TODO: Add your command handler code here	
	ENABLEXYROTATE=!ENABLEXYROTATE;
	ENABLEZROTATE=FALSE;
	ENABLEXYSHIFT=FALSE;
}
void CDemoView::OnZrotate() 
{
	// TODO: Add your command handler code here	
    ENABLEZROTATE=TRUE;
	ENABLEXYROTATE=FALSE;
	ENABLEXYSHIFT=FALSE;
}
void CDemoView::OnXyshift() 
{
	// TODO: Add your command handler code here
//	ENABLEXYSHIFT=TRUE;	
	ENABLEXYSHIFT = !ENABLEXYSHIFT;
	ENABLEXYROTATE=FALSE;
	ENABLEZROTATE=FALSE;
}
void CDemoView::OnResetcam() 
{
	// TODO: Add your command handler code here	
	rot[0]=0;
	rot[1]=0;
	rot[2]=0;
	zoom=-4.5f;
	xyshift[0]=0;
	xyshift[1]=0;
	//Arcball
	Matrix3fSetIdentity(&LastRot);	// Reset Rotation
	Matrix3fSetIdentity(&ThisRot);	// Reset Rotation
    Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);// Reset Rotation
	m_pControlWnd->m_cRotateX.SetPos(0);
	m_pControlWnd->m_cRotateY.SetPos(0);
	m_pControlWnd->m_cRotateZ.SetPos(0);
	m_fRotateX = m_pControlWnd->m_cRotateX.GetPos();
	m_fRotateY = m_pControlWnd->m_cRotateY.GetPos();
	m_fRotateZ = m_pControlWnd->m_cRotateZ.GetPos();

		


	Invalidate(FALSE);
}
void CDemoView::OnAnimate() 
{
	// TODO: Add your command handler code here
	if(ENABLEANIMATE==FALSE)
	{
	    ENABLEANIMATE=TRUE;
	    m_timer=SetTimer(1,15,NULL);
	}
	else
	{
		KillTimer(m_timer);
		ENABLEANIMATE=FALSE;
	}
}
void CDemoView::OnShowaxis() 
{
	// TODO: Add your command handler code here
	SHOWAXIS=!SHOWAXIS;
	Invalidate(FALSE);
}
void CDemoView::OnShowindex() 
{
	// TODO: Add your command handler code here
	SHOWINDEX=!SHOWINDEX;
	Invalidate(FALSE);
}
void CDemoView::OnShowback() 
{
	// TODO: Add your command handler code here
	SHOWBACK=!SHOWBACK;
	Invalidate(FALSE);
}
void CDemoView::OnEnableselect() 
{
	// TODO: Add your command handler code here
	ENABLESELECT=!ENABLESELECT;

	if(ENABLESELECT)
	{
		SetCapture();
		HCURSOR hCursor;
		hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR3);
		SetCursor(hCursor);
	}
	else
		::ReleaseCapture();
}

//消息相应函数//////////////////////////////////////////////////////////////
void CDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//Arcball rotate control
	LastRot=ThisRot;// Set Last Static Rotation To Last Dynamic One
	MousePt.s.X=point.x;
	MousePt.s.Y=point.y;
	ArcBall.click(&MousePt);// Update Start Vector And Prepare For Dragging
	
	if(!ENABLESELECT)
	{
		SetCapture();
		HCURSOR hCursor;
		hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
		SetCursor(hCursor);
	}
	else if(!CTRLKEYDOWN)
	{
		::ReleaseCapture();

		SetCapture();
		HCURSOR hCursor;
		hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);
		SetCursor(hCursor);
	}
	//删除选择的顶点
	if(ENABLESELECT&&CTRLKEYDOWN)
	{
		DeletePnt();
	}

	LButtonSta=TRUE;
	mouseX=point.x;
	mouseY=point.y;
	
	CView::OnLButtonDown(nFlags, point);
}
void CDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(ENABLESELECT)
	{
		//设定光标
		if(!CURSORINWND&&m_oldRect.PtInRect(point))
		{
			SetCapture();
			HCURSOR hCursor;
			hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR3);
			SetCursor(hCursor);
			CURSORINWND=true;
		}
		else if(CURSORINWND&&!m_oldRect.PtInRect(point))
		{
			::ReleaseCapture();
			CURSORINWND=FALSE;
		}
		//进入选择\删除模式
		else if(CURSORINWND&&m_oldRect.PtInRect(point)&&!LButtonSta&&!RButtonSta)
		{
			DoSelect(point);
		}
	}

	if(LButtonSta==TRUE&&!CTRLKEYDOWN)//旋转+平移
	{
//		if(ENABLEXYROTATE==TRUE)
//		{
//		    rot[0]+=(mouseX-point.x);//X
//		    rot[1]+=(mouseY-point.y);//Y
//		}
//		else if(ENABLEZROTATE==TRUE)
//		{
//		    rot[2]+=(mouseX-point.x);//Z
//		}

		if(ENABLEXYSHIFT==TRUE)//平移
		{
		    xyshift[0]-=(mouseX-point.x)/100.0f;
		    xyshift[1]+=(mouseY-point.y)/100.0f;
		}
		else//旋转
		{
			//Arcball rotate control
			Quat4fT ThisQuat;
			GLfloat tmp=.0f;
			MousePt.s.X=point.x;
			MousePt.s.Y=point.y;
			ArcBall.drag(&MousePt,&ThisQuat);// Update End Vector And Get Rotation As Quaternion
			//Add by xuaimei:to acquire value of angle;
			tmp = (ThisQuat.s.W)*2;
			m_RotateAngle= asinf(sqrtf(1-tmp*tmp))*2;
			Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);// Convert Quaternion Into Matrix3fT
			Matrix3fMulMatrix3f(&ThisRot, &LastRot);// Accumulate Last Rotation Into This One
			Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);
		}
	//	RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW);

	}
	else if(RButtonSta==TRUE&&!CTRLKEYDOWN)//缩放
	{
		zoom-=(mouseY-point.y)/10.0f;
	//	RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW);
	}
	mouseX=point.x;
	mouseY=point.y;
	
	if(ENABLEANIMATE==FALSE)
	    Invalidate(FALSE);
	  // RedrawWindow(NULL, NULL, RDW_INVALIDATE|RDW_UPDATENOW);
	
	CView::OnMouseMove(nFlags, point);
}
void CDemoView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!CTRLKEYDOWN)
	{
		::ReleaseCapture();
		if(ENABLESELECT&&CURSORINWND)
		{
			SetCapture();
			HCURSOR hCursor;
			hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR3);
			SetCursor(hCursor);
		}
	}
	
	LButtonSta=FALSE;
	CView::OnLButtonUp(nFlags, point);
}
void CDemoView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!ENABLESELECT)
	{
		SetCapture();
		HCURSOR hCursor;
		hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR2);
		SetCursor(hCursor);
	}
	else if(!CTRLKEYDOWN)
	{
		::ReleaseCapture();

		SetCapture();
		HCURSOR hCursor;
		hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR2);
		SetCursor(hCursor);
	}

	RButtonSta=TRUE;
	mouseX=point.x;
	mouseY=point.y;
	
	CView::OnRButtonDown(nFlags, point);
}
void CDemoView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!CTRLKEYDOWN)
	{
		::ReleaseCapture();
		if(ENABLESELECT&&CURSORINWND)
		{
			SetCapture();
			HCURSOR hCursor;
			hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR3);
			SetCursor(hCursor);
		}
	}
	
	RButtonSta=FALSE;
	CView::OnRButtonUp(nFlags, point);
}
void CDemoView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	rot[0]+=1;
	rot[1]+=1;
	rot[2]+=2;
	Invalidate(FALSE);
	
	CView::OnTimer(nIDEvent);
}
void CDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==0x11)//判断是否是CTRL键
		CTRLKEYDOWN=TRUE;
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CDemoView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==0x11)//判断是否是CTRL键
		CTRLKEYDOWN=FALSE;
	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}
void CDemoView::OnBackward() 
{
	// TODO: Add your command handler code here
	if(nindeleteindex>0)
	{
		//重组恢复删除点后的顶点数组
		dlgload.m_point2d[deleteindex[nindeleteindex-1]][0]=deletecontent[nindeleteindex-1][0];
		dlgload.m_point2d[deleteindex[nindeleteindex-1]][1]=deletecontent[nindeleteindex-1][1];
		dlgload.n2dpoint++;
		dlgload.m_point3d[deleteindex[nindeleteindex-1]][0]=deletecontent[nindeleteindex-1][2];
		dlgload.m_point3d[deleteindex[nindeleteindex-1]][1]=deletecontent[nindeleteindex-1][3];
		dlgload.m_point3d[deleteindex[nindeleteindex-1]][2]=deletecontent[nindeleteindex-1][4];
		dlgload.n3dpoint++;

		//对恢复后的点进行三角化
		int kk=0;
		int &numberoftriangle=kk;		
		int vertexindex[100000];

		dlgload.triangulation(dlgload.m_point2d,dlgload.n2dpoint,vertexindex,numberoftriangle);
		dlgload.ntri=numberoftriangle;

		for(int i=0;i<dlgload.ntri;i++)
		{
			for(int j=0;j<3;j++)
				dlgload.triangle[i][j]=vertexindex[i*3+j];		
		}

		//为撤销恢复操作作准备
		if(nindeleteindex>0)
		{
			nindeleteindex--;
		}
		else
			nindeleteindex=0;

		Invalidate(FALSE);
	}
}
void CDemoView::OnSaveresult() 
{
	// TODO: Add your command handler code here
	FILE* presult;
	presult=fopen("3d_data_md.txt","w");
	for(int i=0;i<dlgload.n3dpoint;i++)
	{
		fprintf(presult,"%f %f %f\n",dlgload.m_point3d[i][0],dlgload.m_point3d[i][1],dlgload.m_point3d[i][2]);
	}
	presult=fopen("matches_md.txt","w");
	for(i=0;i<dlgload.n2dpoint;i++)
	{
		fprintf(presult,"%f %f\n",dlgload.m_point2d[i][0],dlgload.m_point2d[i][1]);
	}
	fclose(presult);	
}
void CDemoView::OnSavetrindex() 
{
	// TODO: Add your command handler code here
	FILE* presult;
	presult=fopen("trindex.txt","w");
	for(int i=0;i<dlgload.ntri;i++)
	{
		fprintf(presult,"%d %d %d\n",dlgload.triangle[i][0],dlgload.triangle[i][1],dlgload.triangle[i][2]);
	}
	fclose(presult);
}

//setcheckbox函数////////////////////////////////////////////////////////
void CDemoView::OnUpdateShowPoints(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(SHOWPOINTS);
}
void CDemoView::OnUpdateShowMesh(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(SHOWTRIMESH);
}
void CDemoView::OnUpdateTextureMapping(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(TEXTURE);
}
void CDemoView::OnUpdateXyrotate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ENABLEXYROTATE);
}
void CDemoView::OnUpdateZrotate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ENABLEZROTATE);
}
void CDemoView::OnUpdateXyshift(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ENABLEXYSHIFT);
}
void CDemoView::OnUpdateAnimate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ENABLEANIMATE);
}
void CDemoView::OnUpdateShowback(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!SHOWBACK);
}
void CDemoView::OnUpdateShowaxis(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(SHOWAXIS);
}
void CDemoView::OnUpdateShowindex(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(SHOWINDEX);
}
void CDemoView::OnUpdateLight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ENABLELIGHT);
}
void CDemoView::OnUpdateEnableselect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(ENABLESELECT);
}

//其他函数/////////////////////////////////////////////////////////////
//计算三角面片的法向量(用于光照)
void CDemoView::CaculateNormal(GLdouble* dVertex1,GLdouble* dVertex2,
							   GLdouble* dVertex3,GLdouble* dNormal)
{
	GLdouble dVector1[3],dVector2[3];
	dVector1[0]=dVertex2[0]-dVertex1[0];
	dVector1[1]=dVertex2[1]-dVertex1[1];
	dVector1[2]=dVertex2[2]-dVertex1[2];
	dVector2[0]=dVertex3[0]-dVertex1[0];
	dVector2[1]=dVertex3[1]-dVertex1[1];
	dVector2[2]=dVertex3[2]-dVertex1[2];

	dNormal[0]=dVector1[1]*dVector2[2]-dVector1[2]*dVector2[1];
	dNormal[1]=dVector1[2]*dVector2[0]-dVector1[0]*dVector2[2];
	dNormal[2]=dVector1[0]*dVector2[1]-dVector1[1]*dVector2[0];

	double dNormalLength=sqrt(dNormal[0]*dNormal[0]+
		                      dNormal[1]*dNormal[1]+dNormal[2]*dNormal[2]);
	if(dNormalLength!=0.0)
	{
		dNormal[0]=dNormal[0]/dNormalLength;
		dNormal[1]=dNormal[1]/dNormalLength;
		dNormal[2]=dNormal[2]/dNormalLength;
	}
	else
	{
		dNormal[0]=0.0;
		dNormal[1]=0.0;
		dNormal[2]=1.0;
	}
}
//开始选择
void CDemoView::DoSelect(CPoint point)
{
	GLint hits;
	GLint vp[4];
	
	glGetIntegerv (GL_VIEWPORT,vp);
	
	glSelectBuffer(1000,selectBuf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(~0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluPickMatrix(point.x,vp[3]-point.y,3,3,vp);
		gluPerspective(45,(GLdouble)m_oldRect.right/(GLdouble)m_oldRect.bottom,0.1,1000.0);
		glMatrixMode(GL_MODELVIEW);
		DrawScene(GL_SELECT);
	glPopMatrix();
	glFlush();

	hits=glRenderMode(GL_RENDER);
	if(hits)
	{
		int n=0;double minz=selectBuf[1];
		for(int i=1;i<hits;i++)
		{
			if (selectBuf[1+i*4]<minz) {n=i;minz=selectBuf[1+i*4];}
		}
		selectindex=selectBuf[n*4+3];
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,m_oldRect.right,m_oldRect.bottom);
	gluPerspective(45,(GLdouble)m_oldRect.right/(GLdouble)m_oldRect.bottom,0.1,1000.0);
}
//删除选择的点
void CDemoView::DeletePnt()
{
	if(dlgload.n3dpoint!=0)
	{
		//为撤销恢复操作作准备
		nindeleteindex++;
		if(nindeleteindex==6)
		{
			for(int i=0;i<4;i++)
			{
				deleteindex[i]=deleteindex[i+1];
				deletecontent[i][0]=deletecontent[i+1][0];
				deletecontent[i][1]=deletecontent[i+1][1];
				deletecontent[i][2]=deletecontent[i+1][2];
				deletecontent[i][3]=deletecontent[i+1][3];
				deletecontent[i][4]=deletecontent[i+1][4];
			}
			deleteindex[4]=selectindex;
			if(dlgload.n2dpoint!=0)
			{
				deletecontent[4][0]=dlgload.m_point2d[selectindex][0];
				deletecontent[4][1]=dlgload.m_point2d[selectindex][1];
				deletecontent[4][2]=dlgload.m_point3d[selectindex][0];
				deletecontent[4][3]=dlgload.m_point3d[selectindex][1];
				deletecontent[4][4]=dlgload.m_point3d[selectindex][2];
				nindeleteindex--;
			}
			else
			{
				deletecontent[4][0]=0;
				deletecontent[4][1]=0;
				deletecontent[4][2]=dlgload.m_point3d[selectindex][0];
				deletecontent[4][3]=dlgload.m_point3d[selectindex][1];
				deletecontent[4][4]=dlgload.m_point3d[selectindex][2];
				nindeleteindex--;			}
		}
		else
		{
			if(dlgload.n2dpoint!=0)
			{
				deleteindex[nindeleteindex-1]=selectindex;
				deletecontent[nindeleteindex-1][0]=dlgload.m_point2d[selectindex][0];
				deletecontent[nindeleteindex-1][1]=dlgload.m_point2d[selectindex][1];
				deletecontent[nindeleteindex-1][2]=dlgload.m_point3d[selectindex][0];
				deletecontent[nindeleteindex-1][3]=dlgload.m_point3d[selectindex][1];
				deletecontent[nindeleteindex-1][4]=dlgload.m_point3d[selectindex][2];
			}
			else
			{
				deleteindex[nindeleteindex-1]=selectindex;
				deletecontent[nindeleteindex-1][0]=0;
				deletecontent[nindeleteindex-1][1]=0;
				deletecontent[nindeleteindex-1][2]=dlgload.m_point3d[selectindex][0];
				deletecontent[nindeleteindex-1][3]=dlgload.m_point3d[selectindex][1];
				deletecontent[nindeleteindex-1][4]=dlgload.m_point3d[selectindex][2];
			}

		}

		//重组删除点后的顶点数组
		if(dlgload.n2dpoint!=0)
		{
			dlgload.m_point2d[selectindex][0]=dlgload.m_point2d[dlgload.n2dpoint-1][0];
			dlgload.m_point2d[selectindex][1]=dlgload.m_point2d[dlgload.n2dpoint-1][1];
			dlgload.n2dpoint--;
		}
		dlgload.m_point3d[selectindex][0]=dlgload.m_point3d[dlgload.n3dpoint-1][0];
		dlgload.m_point3d[selectindex][1]=dlgload.m_point3d[dlgload.n3dpoint-1][1];
		dlgload.m_point3d[selectindex][2]=dlgload.m_point3d[dlgload.n3dpoint-1][2];
		dlgload.n3dpoint--;

		//对剩下的点进行三角化
		if(dlgload.n2dpoint!=0)
		{
			int kk=0;
			int &numberoftriangle=kk;		
			int vertexindex[100000];

			dlgload.triangulation(dlgload.m_point2d,dlgload.n2dpoint,vertexindex,numberoftriangle);
			dlgload.ntri=numberoftriangle;

			for(int i=0;i<dlgload.ntri;i++)
			{
				for(int j=0;j<3;j++)
					dlgload.triangle[i][j]=vertexindex[i*3+j];		
			}
		}

		Invalidate(FALSE);
	}
}

void CDemoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_pFr = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	m_pControlWnd = m_pFr->m_pCtrlWnd;


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
		
		
		lmc1_MarkEntity=(LMC1_MARKENTITY)GetProcAddress(m_hEzdDLL,"lmc1_MarkEntity");
		if(lmc1_MarkEntity==NULL)
		{
			AfxMessageBox(_T("Can not find funtion lmc1_MarkEntity in MarkEzd.dll!"));	
		}

		lmc1_Mark =(LMC1_MARK)GetProcAddress(m_hEzdDLL,"lmc1_Mark");
		if (lmc1_Mark == NULL)
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

		lmc1_SetPenParam = (LMC1_SETPENPARAM)GetProcAddress(m_hEzdDLL,"lmc1_SetPenParam");
		if (lmc1_SetPenParam == NULL)
		{
				AfxMessageBox(_T("Can not find funtion lmc1_SetDevCfg in MarkEzd.dll!"));	

		}
		lmc1_GetPenParam = (LMC1_GETPENPARAM)GetProcAddress(m_hEzdDLL,"lmc1_GetPenParam");
		if (lmc1_GetPenParam == NULL)
		{
				AfxMessageBox(_T("Can not find funtion lmc1_SetDevCfg in MarkEzd.dll!"));	
		}
		lmc1_SaveEntLibToFile = (LMC1_SAVEENTLIBTOFILE)GetProcAddress(m_hEzdDLL,"lmc1_SaveEntLibToFile");
		

	}
	
	int nErr =LMC1_ERR_SUCCESS;

		if(lmc1_Initial!=NULL)
		{
		//	nErr = lmc1_Initial(_T("D:\\EzCad光盘\\EzCad2.1.3_UNICODE(20091023)"),0,GetSafeHwnd());
			nErr = lmc1_Initial(_T("E:\\zhenjing"),0,GetSafeHwnd());

			if(nErr!=LMC1_ERR_SUCCESS)
			{
				CString strErr;
				strErr.Format(_T("Initial lmc1 failed! ErrCode = %d"),nErr);
				AfxMessageBox(strErr);				
			}	
		}
	/*
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
	*/
	


	


}

BOOL CDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

BOOL CDemoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default

		if(zDelta>0)
		{
			zoom-=zDelta/50.0f;

		}
		else
		{
			zoom-=zDelta/50.0f;

		}

	
	this->Invalidate();


	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

