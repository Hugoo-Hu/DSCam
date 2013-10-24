
// DSCamView.h : interface of the CDSCamView class
//

#pragma once


class CDSCamView : public CView
{
protected: // create from serialization only
	CDSCamView();
	DECLARE_DYNCREATE(CDSCamView)

// Attributes
public:
	CDSCamDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CDSCamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DSCamView.cpp
inline CDSCamDoc* CDSCamView::GetDocument() const
   { return reinterpret_cast<CDSCamDoc*>(m_pDocument); }
#endif

