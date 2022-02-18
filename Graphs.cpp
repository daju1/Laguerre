// Graphs.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Graphs.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "GraphsDoc.h"
#include "GraphsView.h"

#define DAYS 45

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphsApp

BEGIN_MESSAGE_MAP(CGraphsApp, CWinApp)
	//{{AFX_MSG_MAP(CGraphsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_COMMAND(ID_FILE_IMPORT2, OnFileImport2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphsApp construction

CGraphsApp::CGraphsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraphsApp object

CGraphsApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {E2BDABAE-8E2C-4525-9365-855A26AB6E0E}
static const CLSID clsid =
{ 0xe2bdabae, 0x8e2c, 0x4525, { 0x93, 0x65, 0x85, 0x5a, 0x26, 0xab, 0x6e, 0xe } };

/////////////////////////////////////////////////////////////////////////////
// CGraphsApp initialization

BOOL CGraphsApp::InitInstance()
{
	///////////////////////////////////////
/*	CString str;

	CTime now, compiled;
	time_t now_t, compiled_t, used_t;
	int used_days, remaine_days;

	now = CTime::GetCurrentTime();
	now_t = now.GetTime();

	compiled = CTime(2003,11,10,0, 0, 0);
	compiled_t = compiled.GetTime();

	used_t = now_t - compiled_t;

	used_days = (int)(used_t / 86400);
	remaine_days = DAYS - used_days;
	if (remaine_days < 31 && remaine_days >=0)
	{
		str.Format("—рок использовани¤ программы\n"
			"истекает через %i дней", remaine_days);
		AfxMessageBox(str);
	}
	if (remaine_days < 0)
	{
		str.Format("—рок использовани¤ программы\n"
			"\tистЄк");
		AfxMessageBox(str);
		return FALSE;
	}
	*/
	///////////////////////////////////////
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Geoindustry"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CMultiDocTemplate(
		IDR_GRAPHSTYPE,
		RUNTIME_CLASS(CGraphsDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGraphsView));
	AddDocTemplate(m_pDocTemplate);

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, m_pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGraphsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsApp message handlers

void CGraphsApp::OnFileImport() 
{
	// создаЄм объект диалога 
	CFileDialog dlg(true);
	CString str, name, ext, path;

	str += "Golden Software Blanking (*.bln)";
	str += (TCHAR)NULL;
	str += "*.bln";
	str += (TCHAR)NULL;

	str += "Coma Separated Values (*.csv)";
	str += (TCHAR)NULL;
	str += "*.csv";
	str += (TCHAR)NULL;

	str += "All files (*.*)";
	str += (TCHAR)NULL;
	str += "*.*";
	str += (TCHAR)NULL;
	// и присваиваем ему необходимые фильтры
	dlg.m_ofn.lpstrFilter = str;
	dlg.m_ofn.nFilterIndex = 2;
	dlg.m_ofn.lpstrTitle = "»мпорт...";
	// выводим диалог на экран и обрабатываем выбранное пользователем им¤ файла, 
	if(dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		name = dlg.GetFileName();
		ext = dlg.GetFileExt();
	}
	else 
	//если пользователь выбрал отмена - выходим
		return;
	// CоздаЄм новый документ
	OnFileNew();
	POSITION posDoc;
	CGraphsDoc* pDoc;
	// и получаем указатель на него
	posDoc = m_pDocTemplate->GetFirstDocPosition();
	while (posDoc !=NULL)
	{
		pDoc = (CGraphsDoc*)m_pDocTemplate->GetNextDoc(posDoc);
	}
	// открываем файл дл¤ чтени¤
	FILE *stream;
	if ((stream = fopen(path,"rt")) == NULL)
	{
		AfxMessageBox("Cannot open input file.\n");
		return;
	}
	const int n=64; // length of buffer string line
	char szBuff[n]; // buffer string line
	double t, f;
	int iComa;
	
	if (ext == "csv")
	{
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				len++;
			}
		}
	    fclose(stream);
		FILE *stream;
		if ((stream = fopen(path,"rt")) == NULL)
		{
			AfxMessageBox("Cannot open input file.\n");
			return;
		}
		pDoc->m_t = vdouble(len);
		pDoc->m_T = vdouble(len);
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				CString line = CString(szBuff);
				iComa = line.Find(",");

				t = atof(line.Left(iComa));
				f = atof(line.Mid(1 + iComa));
				if (i < len)
				{
					pDoc->m_t[i] = t;
					pDoc->m_T[i] = f;
					i++;
				}
			}
		}
		pDoc->m_t0    = pDoc->m_t[0];
		pDoc->m_tend  = pDoc->m_t.End();
		pDoc->m_t2end = pDoc->m_t.End();
		pDoc->m_dt    = pDoc->m_t.DiffVector().Max();
	}
	if (ext == "bln")
	{
		fgets(szBuff,n,stream);
		CString line = CString(szBuff);
		int nlines = atoi(line),
			iline = 0;
		pDoc->m_t = vdouble(nlines + 1);
		pDoc->m_T = vdouble(nlines + 1);
		while (!feof(stream) && iline < nlines)
		{
			fgets(szBuff,n,stream);
			if (!feof(stream) && iline < nlines)
			{
				iline++;
				line = CString(szBuff);
				iComa = line.Find(",");

				t = atof(line.Left(iComa));
				f = atof(line.Mid(1 + iComa));
				
				pDoc->m_t[iline] = t;
				pDoc->m_T[iline] = f;
			}
		}
	}
	fclose(stream);
	pDoc->OnImport();
}


void CGraphsApp::OnFileImport2() 
{
	// создаЄм объект диалога 
	CFileDialog dlg(true);
	CString str, name, ext, path;

	str += "Coma Separated Values (*.csv)";
	str += (TCHAR)NULL;
	str += "*.csv";
	str += (TCHAR)NULL;

	str += "All files (*.*)";
	str += (TCHAR)NULL;
	str += "*.*";
	str += (TCHAR)NULL;
	// и присваиваем ему необходимые фильтры
	dlg.m_ofn.lpstrFilter = str;
	dlg.m_ofn.nFilterIndex = 2;
	dlg.m_ofn.lpstrTitle = "»мпорт 2...";
	// выводим диалог на экран и обрабатываем выбранное пользователем им¤ файла, 
	if(dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		name = dlg.GetFileName();
		ext = dlg.GetFileExt();
	}
	else 
	//если пользователь выбрал отмена - выходим
		return;
	// CоздаЄм новый документ
	OnFileNew();
	POSITION posDoc;
	CGraphsDoc* pDoc;
	// и получаем указатель на него
	posDoc = m_pDocTemplate->GetFirstDocPosition();
	while (posDoc !=NULL)
	{
		pDoc = (CGraphsDoc*)m_pDocTemplate->GetNextDoc(posDoc);
	}
	// открываем файл дл¤ чтени¤
	FILE *stream;
	if ((stream = fopen(path,"rt")) == NULL)
	{
		AfxMessageBox("Cannot open input file.\n");
		return;
	}
	const int n=128; // length of buffer string line
	char szBuff[n]; // buffer string line
	double t, f, f2;
	int iComa;
	
	if (ext == "csv")
	{
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				len++;
			}
		}
	    fclose(stream);
		FILE *stream;
		if ((stream = fopen(path,"rt")) == NULL)
		{
			AfxMessageBox("Cannot open input file.\n");
			return;
		}
		pDoc->m_t = vdouble(len);
		pDoc->m_T = vdouble(len);
		pDoc->m_T2 = vdouble(len);
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				CString line = CString(szBuff);
				iComa = line.Find(",");

				t = atof(line.Left(iComa));

				line = line.Mid(1 + iComa);
				f = atof(line);

				iComa = line.Find(",");
				line = line.Mid(1 + iComa);
				f2 = atof(line);

				if (i < len)
				{
					pDoc->m_t[i] = t;
					pDoc->m_T[i] = f;
					pDoc->m_T2[i] = f2;
					i++;
				}
			}
		}
		pDoc->m_t0    = pDoc->m_t[0];
		pDoc->m_tend  = pDoc->m_t.End();
		pDoc->m_t2end = pDoc->m_t.End();
		pDoc->m_dt    = pDoc->m_t.DiffVector().Max();
	}
	fclose(stream);
	pDoc->OnImport();
}
