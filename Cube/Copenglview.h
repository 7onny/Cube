// COpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "opengl view classdoc.h"
#include <gl\gl.h>
#include <gl\glu.h>


class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLViewClassDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// The following was added

	virtual BOOL SetupPixelFormat( void );
	virtual BOOL SetupViewport( int cx, int cy );
	virtual BOOL SetupViewingFrustum( GLdouble aspect_ratio );
	virtual BOOL SetupViewingTransform( void );
  	virtual BOOL PreRenderScene( void ) { return TRUE; }
 	virtual void RenderStockScene( void );
	virtual BOOL RenderScene( void );



private:
	BOOL InitializeOpenGL();
	void SetError( int e );


	HGLRC	m_hRC;
	CDC*	m_pDC;
	
	static const char* const _ErrorStrings[];
	const char* m_ErrorString;

};

#ifndef _DEBUG  // debug version in COpenGLView.cpp
inline COpenGLViewClassDoc* COpenGLView::GetDocument()
   { return (COpenGLViewClassDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
