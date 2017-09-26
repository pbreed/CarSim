// CarSimView.cpp : implementation of the CCarSimView class
//

#include "stdafx.h"
#include "CarSim.h"

#include "CarSimDoc.h"
#include "CarSimView.h"
#include "ReportDlg.h"
#include "MainFrm.h"
#include "WorldObjects.h"
#include "TheSimCar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCarSimView

IMPLEMENT_DYNCREATE(CCarSimView, CZoomView)

BEGIN_MESSAGE_MAP(CCarSimView, CZoomView)
	//{{AFX_MSG_MAP(CCarSimView)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnViewZoomout)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnViewZoomin)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_COMMAND(ID_RUNSIM, OnRunsim)
	ON_COMMAND(IDC_ZOOMFULL, OnZoomfull)
	ON_COMMAND(IDC_ZOOMCURSOR, OnZoomcursor)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(IDR_RESETSIM, OnResetsim)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_PATH_START, &CCarSimView::OnPathStart)
	ON_COMMAND(ID_PATH_END, &CCarSimView::OnPathEnd)
	ON_COMMAND(ID_PATH_REPORT, &CCarSimView::OnPathReport)
	ON_COMMAND(ID_PATH_CLEAR, &CCarSimView::OnPathClear)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarSimView construction/destruction

CCarSimView::CCarSimView()
{
	// TODO: add construction code here
	zoom_factor=1;

}

CCarSimView::~CCarSimView()
{
}

BOOL CCarSimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CZoomView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCarSimView drawing

void CCarSimView::OnDraw(CDC* pDC)
{
	CCarSimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    

	pDC->SelectStockObject(BLACK_PEN);
	
	WorldObject * po=pDoc->m_pStaticListHead;

    while(po)
	{
	 po->DrawMe(pDC);
	 po=po->m_pNext;
	}

    
	
	po=pDoc->m_pDynamicListHead;

    while(po)
	{
	 po->DrawMe(pDC);
	 po=po->m_pNext;
	}
	
	if (nPathPoints)
	{
		CPen thick_pen(PS_SOLID, 3, RGB(0, 255, 0));
		pDC->SelectObject(thick_pen);
		pDC->MoveTo(PathPoint[0]);
		for (int i = 1; i < nPathPoints; i++)
		{
			pDC->LineTo(PathPoint[i]);
		}
		pDC->SelectStockObject(BLACK_PEN);
	}

/*    int xo=-pDoc->m_xoff;
	int yo=-pDoc->m_yoff;

	//xo=200;
	//yo=200;

    pDC->MoveTo(-20+xo,-20+yo);
	pDC->LineTo(20+xo,20+yo);
	pDC->MoveTo(-20+xo,20+yo);
	pDC->LineTo(20+xo,-20+yo);

	pDC->MoveTo(0+xo,0+yo);
	pDC->LineTo(200+xo,0+yo);
	pDC->MoveTo(0+xo,0+yo);
	pDC->LineTo(0+xo,-200+yo);


*/
	/*for(int i=0; i<2000; i+=200)
	{
	 pDC->MoveTo(0,i);
	 pDC->LineTo(2000,i);
	 pDC->MoveTo(i,0);
	 pDC->LineTo(i,2000);
	 CString str;
	 str.Format("%d",i);
	 pDC->TextOut(1000,i,str);
	 pDC->TextOut(i,1000,str);

	}
	*/
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCarSimView printing

BOOL CCarSimView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCarSimView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCarSimView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCarSimView diagnostics

#ifdef _DEBUG
void CCarSimView::AssertValid() const
{
	CZoomView::AssertValid();
}

void CCarSimView::Dump(CDumpContext& dc) const
{
	CZoomView::Dump(dc);
}

CCarSimDoc* CCarSimView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCarSimDoc)));
	return (CCarSimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCarSimView message handlers



void CCarSimView::OnPause() 
{
//	SetCbarText(2,"Paused");
	KillTimer(TimerId);
}

void CCarSimView::OnRunsim() 
{
	SetCbarText(2,"Running");
	TimerId=SetTimer(1,50,NULL);
}


void CCarSimView::SetCbarText(int index,const char * txt)
{
CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
CStatusBar* pSBar = &pFrame->m_wndStatusBar;
pSBar->SetPaneText(index,txt,TRUE);
}

void CCarSimView::OnInitialUpdate() 
{
	
     CZoomView::OnInitialUpdate();
	 SetViewRegion(GetDocument()->GetSize());
	 m_PathMode = false;
	 nPathPoints = 0;
	 
	
// TODO: Add your specialized code here and/or call the base class
	
}



void CCarSimView::OnViewZoomin() 
{
	 DoZoomIn();
}
void CCarSimView::OnViewZoomout() 
{
 DoZoomOut();
} 

void CCarSimView::OnZoomfull() 
{
 DoZoomFull();
	
}

void CCarSimView::OnZoomcursor() 
{
	// TODO: Add your command handler code here
	SetZoomMode(MODE_ZOOMIN);

}

BOOL CCarSimView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CZoomView::OnEraseBkgnd(pDC);
}


void CCarSimView::NotifyZoom(void)
{
CString msg;
 msg.Format("Zoom = %g",m_zoomScale);
		SetCbarText(2,msg);
}

void CCarSimView::OnTimer(UINT nIDEvent) 
{
		CZoomView::OnTimer(nIDEvent);

		CCarSimDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->pCar->DoTimeStep(0.02,pDoc->m_pStaticListHead);

		Invalidate(true);
		CString msg;
	    msg.Format("%+6.2f H:%4.0f,%4.0f Odo=%6.0f DO=%6.0f mode=%20s",pDoc->pCar->m_side_range,pDoc->pCar->m_target_h,pDoc->pCar->m_heading, pDoc->pCar->odometer,pDoc->pCar->DeltaOdo(),pDoc->pCar->GetModeName());
		SetCbarText(1,msg);
		
    
}

void CCarSimView::OnResetsim() 
{
	// TODO: Add your command handler code here
		CCarSimDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->pCar->Restart();
	
}


void CCarSimView::MouseAction(CPoint p, bool down)
{
	if (down) m_mDown = p;
	else
	{
		if (m_PathMode)
		{
			PathPoint[nPathPoints++] = p;
			if (nPathPoints > 2)
			{
				Invalidate(true);
			}
		}
	
    }

}

void CCarSimView::OnPathStart()
{
	m_PathMode = true;
}
	


void CCarSimView::OnPathEnd()
{
	m_PathMode = false;
}


void CCarSimView::OnPathReport()
{
	ReportDlg rd(this);
	rd.SetData(nPathPoints, PathPoint);
	rd.DoModal();

	// TODO: Add your command handler code here
}


void CCarSimView::OnPathClear()
{
	nPathPoints = 0;
	// TODO: Add your command handler code here
}
