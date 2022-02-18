// OutLagDoc.cpp : implementation of the COutLagDoc class
//

#include "stdafx.h"
#include "Graphs.h"

#include "OutLagDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutLagDoc

IMPLEMENT_DYNCREATE(COutLagDoc, CDocument)

BEGIN_MESSAGE_MAP(COutLagDoc, CDocument)
	//{{AFX_MSG_MAP(COutLagDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COutLagDoc, CDocument)
	//{{AFX_DISPATCH_MAP(COutLagDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOutLag to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C31EF026-30DC-47FF-AFA7-BDC884C727B0}
static const IID IID_IOutLag =
{ 0xc31ef026, 0x30dc, 0x47ff, { 0xaf, 0xa7, 0xbd, 0xc8, 0x84, 0xc7, 0x27, 0xb0 } };

BEGIN_INTERFACE_MAP(COutLagDoc, CDocument)
	INTERFACE_PART(COutLagDoc, IID_IOutLag, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutLagDoc construction/destruction

COutLagDoc::COutLagDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

COutLagDoc::~COutLagDoc()
{
	AfxOleUnlockApp();
}

BOOL COutLagDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutLagDoc serialization

void COutLagDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutLagDoc diagnostics

#ifdef _DEBUG
void COutLagDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutLagDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutLagDoc commands
