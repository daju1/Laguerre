// OutLagFrm.cpp : implementation file
//

#include "stdafx.h"
#include "Graphs.h"
#include "OutLagFrm.h"
#include "GraphsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutLagFrm

IMPLEMENT_DYNCREATE(COutLagFrm, CFrameWnd)

COutLagFrm::COutLagFrm()
{
	EnableAutomation();
}

COutLagFrm::~COutLagFrm()
{
}

void COutLagFrm::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CFrameWnd::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(COutLagFrm, CFrameWnd)
	//{{AFX_MSG_MAP(COutLagFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COutLagFrm, CFrameWnd)
	//{{AFX_DISPATCH_MAP(COutLagFrm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOutLagFrm to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {0D30EA8A-E113-40F0-AC18-3FDAFF58C57D}
static const IID IID_IOutLagFrm =
{ 0xd30ea8a, 0xe113, 0x40f0, { 0xac, 0x18, 0x3f, 0xda, 0xff, 0x58, 0xc5, 0x7d } };

BEGIN_INTERFACE_MAP(COutLagFrm, CFrameWnd)
	INTERFACE_PART(COutLagFrm, IID_IOutLagFrm, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutLagFrm message handlers

BOOL COutLagFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.x = 240; cs.y = 200; 
	cs.cx = 220; cs.cy = 80;

	return TRUE;
	
}

void COutLagFrm::PostNcDestroy() 
{
	m_pGraphsDoc->m_isOutWnd = false;
	
	CFrameWnd::PostNcDestroy();
}
