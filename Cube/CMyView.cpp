#include "CMyView.h"

IMPLEMENT_DYNCREATE(CMyView, COpenGLView)

BEGIN_MESSAGE_MAP(CMyView, COpenGLView)
	//{{AFX_MSG_MAP(COpenGLView)
	
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BOOL CMyView::RenderScene()
{
	GLfloat LightAmbient[] =  { 0.1f, 0.1f, 0.1f, 0.1f};
	GLfloat LightDiffuse[] =  { 0.7f, 0.7f, 0.7f, 0.7f};
	GLfloat LightSpecular[] = { 0.0f, 0.0f, 0.0f, 0.1f};
	GLfloat LightPosition[] = { 5.0f, 5.0f, 5.0f, 0.0f}; 

	GLfloat RedSurface[]   = { 1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat GreenSurface[] = { 0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat BlueSurface[]  = { 0.0f, 0.0f, 1.0f, 1.0f};

	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	::glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	::glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	::glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
	::glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	::glEnable(GL_LIGHT0);

	::glPushMatrix();	
		::glTranslated(0.0, 0.0, -5.0);
		//added code for mouse rotation
		COpenGLViewClassDoc *pDoc=GetDocument();
		::glRotated(pDoc->rotx,1,0,0);
		::glRotated(pDoc->roty,0,1,0);
		//end of added code

		::glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RedSurface);
		::glBegin(GL_POLYGON);
			::glNormal3d(  1.0,  0.0,  0.0);
			::glVertex3d(  1.0,  1.0,  1.0);
			::glVertex3d(  1.0, -1.0,  1.0);
			::glVertex3d(  1.0, -1.0, -1.0);
			::glVertex3d(  1.0,  1.0, -1.0);
		::glEnd();

		::glBegin(GL_POLYGON);
			::glNormal3d( -1.0,  0.0,  0.0);
			::glVertex3d( -1.0, -1.0,  1.0);
			::glVertex3d( -1.0,  1.0,  1.0);
			::glVertex3d( -1.0,  1.0, -1.0);
			::glVertex3d( -1.0, -1.0, -1.0);
		::glEnd();

		::glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, GreenSurface);
		::glBegin(GL_POLYGON);
			::glNormal3d(  0.0,  1.0,  0.0);
			::glVertex3d(  1.0,  1.0,  1.0);
			::glVertex3d( -1.0,  1.0,  1.0);
			::glVertex3d( -1.0,  1.0, -1.0);
			::glVertex3d(  1.0,  1.0, -1.0);
		::glEnd();				  

		::glBegin(GL_POLYGON);
			::glNormal3d(  0.0, -1.0,  0.0);
			::glVertex3d( -1.0, -1.0,  1.0);
			::glVertex3d(  1.0, -1.0,  1.0);
			::glVertex3d(  1.0, -1.0, -1.0);
			::glVertex3d( -1.0, -1.0, -1.0);
		::glEnd();

		::glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, BlueSurface);
		::glBegin(GL_POLYGON);
			::glNormal3d(  0.0,  0.0,  1.0);
			::glVertex3d(  1.0,  1.0,  1.0);
			::glVertex3d( -1.0,  1.0,  1.0);
			::glVertex3d( -1.0, -1.0,  1.0);
			::glVertex3d(  1.0, -1.0,  1.0);
		::glEnd();

		::glBegin(GL_POLYGON);
			::glNormal3d(  0.0,  0.0, -1.0);
			::glVertex3d( -1.0,  1.0, -1.0);
			::glVertex3d(  1.0,  1.0, -1.0);
			::glVertex3d(  1.0, -1.0, -1.0);
			::glVertex3d( -1.0, -1.0, -1.0);
		::glEnd();
	::glPopMatrix();
	return TRUE;
}



BOOL CMyView::PreRenderScene( void )
{
	::glDrawBuffer( GL_BACK );
	::glEnable( GL_LIGHTING );
	return TRUE;
}

void CMyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CurrentPoint=point;
	IsLButtonDown=true;

	COpenGLView::OnLButtonDown(nFlags, point);
}


void CMyView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	IsLButtonDown=false;

	COpenGLView::OnLButtonUp(nFlags, point);
}


void CMyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	double new_rotation;
	if(IsLButtonDown){
		COpenGLViewClassDoc *pDoc=GetDocument();

		new_rotation=point.x-CurrentPoint.x;
		pDoc->roty+=new_rotation/2;
		new_rotation=point.y-CurrentPoint.y;
		pDoc->rotx+=new_rotation/2;

		CurrentPoint=point;

		InvalidateRect(FALSE);
	}
	else
		COpenGLView::OnMouseMove(nFlags, point);
}
