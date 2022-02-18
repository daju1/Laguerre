// ParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphs.h"
#include "GraphsDoc.h"
#include "ParamDlg.h"
//#include "vdouble.h"
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
/////////////////////////////////////////////////////////////////////////////
// CParamDlg dialog
IMPLEMENT_DYNAMIC(CParamDlg, CDialog)

CParamDlg::CParamDlg(CGraphsDoc* p)
//: CDialog(CParamDlg::IDD, p)
{
	m_is_buzi = false;
	m_pDoc = p;
	//===== Начальное значение свойств среды
	//===== не должно равняться нулю
//	m_Prop = 1.0;
//	m_PropId1 = 0;
//	m_PropId2 = 0;
//	m_Source = 0.0;
//	m_SrcId1 = 0;
//	m_SrcId2 = 0;
}


CParamDlg::CParamDlg(CWnd* pParent)
	: CDialog(CParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParamDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CParamDlg::DoDataExchange(CDataExchange* pDX)
{
	m_is_buzi = true;
//	DDX_Text(pDX, IDC_SIGNAL2, m_pDoc->m_Signal_t0);
	DDX_Text(pDX, IDC_SIGNAL1, m_pDoc->m_i0);

	DDX_Text(pDX, IDC_SIGNAL, m_pDoc->m_SignalNumber);
	DDV_MinMaxInt(pDX, m_pDoc->m_SignalNumber, 1, 10);

	DDX_Text(pDX, IDC_TIME3, m_pDoc->m_t2end);
	DDX_Text(pDX, IDC_TIME2, m_pDoc->m_tend);
	DDX_Text(pDX, IDC_TIME1, m_pDoc->m_dt);
	DDX_Text(pDX, IDC_TIME, m_pDoc->m_t0);
	
	//========= Обмен с переменными оконного класса
	DDX_Text(pDX, IDC_ALPHA, m_pDoc->m_alpha);
	DDX_Text(pDX, IDC_BETA, m_pDoc->m_beta);
	DDX_Text(pDX, IDC_EPSILON, m_pDoc->m_epsilon);
	DDX_Text(pDX, IDC_MAXORDER, m_pDoc->m_MaxOrder);


	DDX_Text(pDX, IDC_ERROR2, m_pDoc->m_PredictError);
	DDX_Text(pDX, IDC_ERROR, m_pDoc->m_error);
	DDX_Text(pDX, IDC_ALPHADET, m_pDoc->m_alpha_det);
	DDX_Text(pDX, IDC_FUNDET, m_pDoc->m_fund_det);

	CDialog::DoDataExchange(pDX);
	m_is_buzi = false;
}


BEGIN_MESSAGE_MAP(CParamDlg, CDialog)
	//{{AFX_MSG_MAP(CParamDlg)
	ON_BN_CLICKED(IDC_ANALIT_STRING, OnClickedAnalitString)
	ON_BN_CLICKED(IDC_ANALIT_SAVE, OnClickedAnalitSave)
	ON_BN_CLICKED(IDC_OUTLAG, OnClickedOutWindow)
	ON_BN_CLICKED(IDC_APPLY, OnClickedApply)
	ON_BN_CLICKED(IDC_APPLY2, OnClickedApply2)
	ON_BN_CLICKED(IDC_ADDSIGNAL1, OnClickedAddSignal1)
	ON_BN_CLICKED(IDC_ADDSIGNAL2, OnClickedAddSignal2)
	ON_BN_CLICKED(IDC_SETTIME, OnClickedSetTime)
	ON_BN_CLICKED(IDC_SETTIMEEND, OnClickedSetTimeEnd)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTONALPHA, OnButtonalpha)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamDlg message handlers

void CParamDlg::OnClickedApply(void)
{
	if (m_is_buzi)
		return;
	m_is_buzi = true;
	//====== Считываем данные из окон
	UpdateData();
	//====== Заново решаем систему и выводим график
	m_pDoc->Solve();

	UpdateData(false);
	m_is_buzi = false;

}
void CParamDlg::OnClickedApply2(void)
{
	if (m_is_buzi)
		return;
	m_is_buzi = true;
	//====== Считываем данные из окон
	UpdateData();
	//====== Заново решаем систему и выводим график
	m_pDoc->TrainNnet();

	UpdateData(false);
	m_is_buzi = false;

}

void CParamDlg::OnClickedSetTime()
{
	if (m_is_buzi)
		return;
	m_is_buzi = true;
	UpdateData();
	m_pDoc->SetTime();
	m_is_buzi = false;
}
void CParamDlg::OnClickedSetTimeEnd()
{
	if (m_is_buzi)
		return;
	m_is_buzi = true;
	UpdateData();
	m_pDoc->SetTimeEnd();
	m_is_buzi = false;
}

void CParamDlg::OnClickedAddSignal(int n) 
{
	int i;
	if (m_is_buzi)
		return;
	m_is_buzi = true;
	UpdateData();

	double ti, dt, Ti;
	dt = m_pDoc->m_dt;
	int N = m_pDoc->m_SignalNumber;

	ti = m_pDoc->m_t0 - m_pDoc->m_dt;
	for(i=m_pDoc->m_i0; i<m_pDoc->m_Len; i++)
	{
		ti+=dt;
		switch (N)
		{
		case 1: 
			Ti = 3 * exp( - .2 * ti);
			break;
		case 2:
			Ti = 5.0 * cos(2.0 * ti);
			break;
		case 3:
			Ti = 2.0 * exp(-0.1*ti)*cos(3.1606961*ti);
			break;
		case 4:
			Ti = 2.0 - 2.0 * exp(-0.1*ti)*cos(3.1606961*ti);
			break;
		case 5:
			Ti = 10.0 * exp( - 0.2 * ti);
			break;
		case 6:
			Ti = 10.0 - 10.0 * exp( - 0.2 * ti);
			break;
		case 7:
			Ti = 5.0 * cos(2.0 * ti) * sin(0.2 * ti);
			break;
		case 8:
			Ti = 5.0 - 5.0 * cos(2.0 * ti) * sin(0.2 * ti);
			break;
		case 9:
			Ti = 5.0 * cos(2.0 * ti) * sin(0.2 * ti) * exp(-0.05 * ti);
			break;
		case 10:
			Ti = 5.0 - 5.0 * cos(2.0 * ti) * sin(0.2 * ti) * exp(-0.05 * ti);
			break;
		}
		if (n == 1)
			m_pDoc->m_T[i] += Ti;
		if (n == 2)
			m_pDoc->m_T2[i] += Ti;
	}
	for( i = 0; i < m_pDoc->m_LenPredict; i++)
	{
		ti+=dt;
		switch (N)
		{
		case 1: 
			Ti = 3 * exp( - .2 * ti);
			break;
		case 2:
			Ti = 5.0 * cos(2.0 * ti);
			break;
		case 3:
			Ti = 2.0 * exp(-0.1*ti)*cos(3.1606961*ti);
			break;
		case 4:
			Ti = 2.0 - 2.0 * exp(-0.1*ti)*cos(3.1606961*ti);
			break;
		case 5:
			Ti = 10.0 * exp( - 0.2 * ti);
			break;
		case 6:
			Ti = 10.0 - 10.0 * exp( - 0.2 * ti);
			break;
		case 7:
			Ti = 5.0 * cos(2.0 * ti) * sin(0.2 * ti);
			break;
		case 8:
			Ti = 5.0 - 5.0 * cos(2.0 * ti) * sin(0.2 * ti);
			break;
		case 9:
			Ti = 5.0 * cos(2.0 * ti) * sin(0.2 * ti) * exp(-0.05 * ti);
			break;	
		case 10:
			Ti = 5.0 - 5.0 * cos(2.0 * ti) * sin(0.2 * ti) * exp(-0.05 * ti);
			break;	
		}
		if (n == 1)
			m_pDoc->m_TPredict[i] += Ti;
		if (n == 2)
			m_pDoc->m_T2Predict[i] += Ti;
	}
	m_pDoc->AddSignal();
	m_is_buzi = false;
}
void CParamDlg::OnButtonalpha() 
{
	if (m_is_buzi)
		return;
	m_is_buzi = true;
	UpdateData();
	m_pDoc->AlphaDeterminition();
	UpdateData(false);
	m_is_buzi = false;

}

void CParamDlg::OnClickedCancel(void)
{
	if (m_is_buzi)
		return;
	//====== Закрываем немодальный диалог
	m_pDoc->m_pDlg = 0;
	DestroyWindow();
}

BOOL CParamDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect r;
	//===== С помощью контекста устройства
	//===== узнаем размеры всего экрана
	CClientDC dc(this);
	int w = dc.GetDeviceCaps(HORZRES);
	int h = dc.GetDeviceCaps(VERTRES);

	//===== Узнаем размеры окна диалога
	GetWindowRect(&r);
	//===== Смещаем его вправо и вниз
	r.OffsetRect(w-r.right-10,h-r.bottom-30);
	MoveWindow(&r);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CParamDlg::PostNcDestroy() 
{
	delete this;
	CDialog::PostNcDestroy();
}

void CParamDlg::OnClickedOutWindow(void)
{
	if (m_is_buzi)
		return;
	//====== Считываем данные из окон
	UpdateData();
	//====== Заново решаем систему и выводим график
	m_pDoc->OutWindow();

	UpdateData(false);
	m_is_buzi = false;
}

void CParamDlg::OnClickedAnalitString()
{
	if (m_is_buzi)
		return;
	//====== Считываем данные из окон
	UpdateData();
	m_pDoc->AnaliticalString();

	UpdateData(false);
	m_is_buzi = false;

}

void CParamDlg::OnClickedAnalitSave()
{
	if (m_is_buzi)
		return;
	//====== Считываем данные из окон
	UpdateData();
	m_pDoc->SaveAnaliticalString();

	UpdateData(false);
	m_is_buzi = false;

}
