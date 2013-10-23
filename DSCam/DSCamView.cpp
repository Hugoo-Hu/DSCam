
// DSCamView.cpp : implementation of the CDSCamView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DSCam.h"
#endif

#include "DSCamDoc.h"
#include "DSCamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDSCamView

IMPLEMENT_DYNCREATE(CDSCamView, CView)

BEGIN_MESSAGE_MAP(CDSCamView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDSCamView construction/destruction

CDSCamView::CDSCamView()
{
	// TODO: add construction code here

}

CDSCamView::~CDSCamView()
{
}

BOOL CDSCamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDSCamView drawing

void CDSCamView::OnDraw(CDC* /*pDC*/)
{
	CDSCamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CDSCamView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDSCamView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDSCamView diagnostics

#ifdef _DEBUG
void CDSCamView::AssertValid() const
{
	CView::AssertValid();
}

void CDSCamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSCamDoc* CDSCamView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSCamDoc)));
	return (CDSCamDoc*)m_pDocument;
}
#endif //_DEBUG


// CDSCamView message handlers
