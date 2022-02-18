#if !defined(AFX_OUTLAGFRM_H__4874DE66_9AA3_4B05_A351_03D33902D691__INCLUDED_)
#define AFX_OUTLAGFRM_H__4874DE66_9AA3_4B05_A351_03D33902D691__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutLagFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutLagFrm frame
class CGraphsDoc;
class COutLagFrm : public CFrameWnd
{
	friend CGraphsDoc;
	DECLARE_DYNCREATE(COutLagFrm)
protected:
	COutLagFrm();           // protected constructor used by dynamic creation
CGraphsDoc *m_pGraphsDoc;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutLagFrm)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~COutLagFrm();

	// Generated message map functions
	//{{AFX_MSG(COutLagFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COutLagFrm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTLAGFRM_H__4874DE66_9AA3_4B05_A351_03D33902D691__INCLUDED_)
