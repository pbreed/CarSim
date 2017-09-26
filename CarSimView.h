// CarSimView.h : interface of the CCarSimView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARSIMVIEW_H__4F64F3A2_0B50_4018_BCE7_346BCB5F0204__INCLUDED_)
#define AFX_CARSIMVIEW_H__4F64F3A2_0B50_4018_BCE7_346BCB5F0204__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "zoomview.h"

class CCarSimView : public CZoomView
{
protected: // create from serialization only
	CCarSimView();
	DECLARE_DYNCREATE(CCarSimView)

// Attributes
public:
	CCarSimDoc* GetDocument();
	CPoint m_mDown;
	bool m_PathMode;
	int nPathPoints;
	CPoint PathPoint[2000];
	




// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCarSimView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCarSimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void NotifyZoom(void);
protected:
   int zoom_factor;
  int  TimerId;

  virtual void MouseAction(CPoint p, bool down);

void SetCbarText(int index,const char * txt);
// Generated message map functions
protected:
	//{{AFX_MSG(CCarSimView)
	afx_msg void OnViewZoomout();
	afx_msg void OnViewZoomin();
	afx_msg void OnPause();
	afx_msg void OnRunsim();
	afx_msg void OnZoomfull();
	afx_msg void OnZoomcursor();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnResetsim();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPathStart();
	afx_msg void OnPathEnd();
	afx_msg void OnPathReport();
	afx_msg void OnPathClear();
};

#ifndef _DEBUG  // debug version in CarSimView.cpp
inline CCarSimDoc* CCarSimView::GetDocument()
   { return (CCarSimDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CARSIMVIEW_H__4F64F3A2_0B50_4018_BCE7_346BCB5F0204__INCLUDED_)
