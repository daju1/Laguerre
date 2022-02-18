// GraphsView.cpp : implementation of the CGraphsView class
//

#include "stdafx.h"
#include "Graphs.h"

#include "GraphsDoc.h"
#include "GraphsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphsView

IMPLEMENT_DYNCREATE(CGraphsView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphsView, CScrollView)
	//{{AFX_MSG_MAP(CGraphsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphsView construction/destruction

CGraphsView::CGraphsView()
{
	// TODO: add construction code here

}

CGraphsView::~CGraphsView()
{
}

BOOL CGraphsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView drawing

void CGraphsView::OnDraw(CDC* pDC)
{
	TData DataX, 
		DataY;
	CGraphsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int a = 65,
		b = 132;
	CGraph(pDoc->m_vpPoints1, "Сигнал для Лаггер - обработки", 
		"t","").Draw(pDC,DataX, DataY);

}

void CGraphsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView printing

BOOL CGraphsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsView diagnostics

#ifdef _DEBUG
void CGraphsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphsDoc* CGraphsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphsDoc)));
	return (CGraphsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphsView message handlers
