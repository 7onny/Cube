#include "Copenglview.h"


class CMyView : public COpenGLView {

private:
	DECLARE_DYNCREATE(CMyView);
protected:
	virtual BOOL RenderScene( void );
	virtual BOOL PreRenderScene( void );


	DECLARE_MESSAGE_MAP()
public:
	CPoint CurrentPoint;
	bool IsLButtonDown;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};