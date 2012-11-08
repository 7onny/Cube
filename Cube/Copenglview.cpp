// COpenGLView.cpp : implementation of the COpenGLView class
//

#include "stdafx.h"
#include "OpenGL View Class.h"

#include "OpenGL View ClassDoc.h"
#include "COpenGLView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



const char* const COpenGLView::_ErrorStrings[]= {
				{"No Error"},					// 0
				{"Unable to get a DC"},			// 1
				{"ChoosePixelFormat failed"},	// 2
				{"SelectPixelFormat failed"},	// 3
				{"wglCreateContext failed"},	// 4
				{"wglMakeCurrent failed"},		// 5
				{"wglDeleteContext failed"},	// 6
				{"SwapBuffers failed"},			// 7

		};

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView() :
	 m_hRC(0), m_pDC(0), m_ErrorString(_ErrorStrings[0])

{
	// TODO: add construction code here

}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	// An OpenGL window must be created with the following flags and must not
    // include CS_PARENTDC for the class style. 
    cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
  	
	return CView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing


void COpenGLView::OnDraw(CDC* pDC)
{
	COpenGLViewClassDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	PreRenderScene();

	::glPushMatrix();
	RenderStockScene();
	::glPopMatrix();

	::glPushMatrix();
	RenderScene();
	::glPopMatrix();

	::glFinish();

	if ( FALSE == ::SwapBuffers( m_pDC->GetSafeHdc() ) )
		{
		SetError(7);
		}
}


/////////////////////////////////////////////////////////////////////////////
// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLViewClassDoc* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLViewClassDoc)));
	return (COpenGLViewClassDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	InitializeOpenGL();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// GL helper functions

void COpenGLView::SetError( int e )
{
	// if there was no previous error,
	// then save this one
	if ( _ErrorStrings[0] == m_ErrorString ) 
		{
		m_ErrorString = _ErrorStrings[e];
		}
}


BOOL COpenGLView::InitializeOpenGL()
{
	// Can we put this in the constructor?
    m_pDC = new CClientDC(this);

    if ( NULL == m_pDC ) // failure to get DC
		{
		SetError(1);
		return FALSE;
		}

	if (!SetupPixelFormat())
		{
        return FALSE;
		}

    //n = ::GetPixelFormat(m_pDC->GetSafeHdc());
    //::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

  //  CreateRGBPalette();

    if ( 0 == (m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) )
		{
		SetError(4);
		return FALSE;
		}

    if ( FALSE == ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
		{
		SetError(5);
		return FALSE;
		}	

	// specify black as clear color
    ::glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	// specify the back of the buffer as clear depth
    ::glClearDepth( 1.0f );
	// enable depth testing
    ::glEnable( GL_DEPTH_TEST );

	return TRUE;
}


BOOL COpenGLView::SetupPixelFormat()
{
  static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
          PFD_SUPPORT_OPENGL |          // support OpenGL
          PFD_DOUBLEBUFFER,             // double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
//        32,                             // 32-bit z-buffer
		16,	// NOTE: better performance with 16-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    int pixelformat;

    if ( 0 == (pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) )
	    {
		SetError(2);
        return FALSE;
		}

    if ( FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) )
	    {
       	SetError(3);
        return FALSE;
		}

    return TRUE;
}

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here

    if ( FALSE == ::wglDeleteContext( m_hRC ) )
		{
		SetError(6);
 		}

    if ( m_pDC )
		{
        delete m_pDC;
		}
}


BOOL COpenGLView::OnEraseBkgnd( CDC* pDC ) 
{
	// TODO: Add your message handler code here and/or call default
	
	//	return CView::OnEraseBkgnd(pDC);
	return TRUE; // tell Windows not to erase the background
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	GLdouble aspect_ratio; // width/height ratio
	
	if ( 0 >= cx || 0 >= cy )
		{
		return;
		}


	SetupViewport( cx, cy );

	// select the projection matrix and clear it
    ::glMatrixMode( GL_PROJECTION );
    ::glLoadIdentity();

	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;

	// select the viewing volumn
	SetupViewingFrustum( aspect_ratio );
	
	// switch back to the modelview matrix
    ::glMatrixMode( GL_MODELVIEW );
    ::glLoadIdentity();

	// now perform any viewing transformations
	SetupViewingTransform();
}

 /////////////////////////////////////////////////////////////////////////////
// COpenGLView helper functions

BOOL COpenGLView::SetupViewport( int cx, int cy )
{
	// select the full client area
    ::glViewport(0, 0, cx, cy);

	return TRUE;
}

BOOL COpenGLView::SetupViewingFrustum( GLdouble aspect_ratio )
{
	// select a default viewing volumn
   ::gluPerspective( 40.0f, aspect_ratio, .1f, 20.0f );
	return TRUE;
}


BOOL COpenGLView::SetupViewingTransform()
{
	// select a default viewing transformation
	// of a 20 degree rotation about the X axis
	// then a -5 unit transformation along Z
	//	::glTranslatef( 0.0f, 0.0f, -5.0f );
	//	::glRotatef( 20.0f, 1.0f, 0.0f, 0.0f );
    return TRUE;
}


BOOL COpenGLView::RenderScene()
{
	// draw a red wire sphere inside a
	// light blue cube

	// rotate the wire sphere so it's vertically
	// oriented
	//::glRotatef( 90.0f, 1.0f, 0.0f, 0.0f );
	//::glColor3f( 1.0f, 0.0f, 0.0f );
	//::auxWireSphere( .5 );
	//::glColor3f( 0.5f, 0.5f, 1.0f );
	//::auxWireCube( 1.0 );
    return TRUE;
}	

// Draw a square surface that looks like a
// black and white checkerboard
void COpenGLView::RenderStockScene()
{
	// define all vertices   X     Y     Z
	GLfloat v0[3], v1[3], v2[3], v3[3], delta;
	int color = 0;

	delta = 0.5f;

	// define the two colors
	GLfloat color1[3] = { 0.9f, 0.9f, 0.9f };
 	GLfloat color2[3] = { 0.05f, 0.05f, 0.05f };

	v0[1] = v1[1] = v2[1] = v3[1] = 0.0f;

	::glBegin( GL_QUADS );

	for ( int x = -5 ; x <= 5 ; x++ )
		{
		for ( int z = -5 ; z <= 5 ; z++ )
			{
			::glColor3fv( (color++)%2 ? color1 : color2 );
		
			v0[0] = 0.0f+delta*z;
			v0[2] = 0.0f+delta*x;

			v1[0] = v0[0]+delta;
			v1[2] = v0[2];

			v2[0] = v0[0]+delta;
			v2[2] = v0[2]+delta;

			v3[0] = v0[0];
			v3[2] = v0[2]+delta;

			::glVertex3fv( v0 );
			::glVertex3fv( v1 );
			::glVertex3fv( v2 );
			::glVertex3fv( v3 );
			}
		}
	::glEnd();	
}


