// OutLagView.h : interface of the COutLagView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTLAGVIEW_H__2BE64E14_F33F_4EA3_AA66_AFEC24527A35__INCLUDED_)
#define AFX_OUTLAGVIEW_H__2BE64E14_F33F_4EA3_AA66_AFEC24527A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutLagView : public CScrollView
{
protected: // create from serialization only
	COutLagView();
	DECLARE_DYNCREATE(COutLagView)

// Attributes
public:
	COutLagDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutLagView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutLagView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutLagView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutLagView.cpp
inline COutLagDoc* COutLagView::GetDocument()
   { return (COutLagDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLAGVIEW_H__2BE64E14_F33F_4EA3_AA66_AFEC24527A35__INCLUDED_)
