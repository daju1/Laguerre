// OutLagView.cpp : implementation of the COutLagView class
//

#include "stdafx.h"
#include "Graphs.h"

#include "OutLagDoc.h"
#include "OutLagView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutLagView

IMPLEMENT_DYNCREATE(COutLagView, CScrollView)

BEGIN_MESSAGE_MAP(COutLagView, CScrollView)
	//{{AFX_MSG_MAP(COutLagView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutLagView construction/destruction

COutLagView::COutLagView()
{
	// TODO: add construction code here

}

COutLagView::~COutLagView()
{
}

BOOL COutLagView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutLagView drawing

void COutLagView::OnDraw(CDC* pDC)
{
	COutLagDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void COutLagView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// COutLagView printing

BOOL COutLagView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COutLagView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COutLagView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COutLagView diagnostics

#ifdef _DEBUG
void COutLagView::AssertValid() const
{
	CScrollView::AssertValid();
}

void COutLagView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

COutLagDoc* COutLagView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutLagDoc)));
	return (COutLagDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutLagView message handlers
