#if !defined(AFX_PARAMDLG_H__7F099925_A667_46F9_9E5D_AEDE379EF5B7__INCLUDED_)
#define AFX_PARAMDLG_H__7F099925_A667_46F9_9E5D_AEDE379EF5B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamDlg dialog

class CParamDlg : public CDialog
{
	//===== Ѕудем общатьс¤ с ƒќ ”ћ≈Ќ“ќћ
	friend class CGraphsDoc;
	DECLARE_DYNAMIC(CParamDlg)

// Construction
public:
	//===== Ѕудем помнить его адрес
	CGraphsDoc *m_pDoc;
	//===== ¬ конструкторе запросим его адрес
	CParamDlg(CGraphsDoc* p);
	virtual ~CParamDlg(){}

	// Dialog Data
	enum { IDD = IDD_PARAM };
	CParamDlg(CWnd* pParent = NULL);   // standard constructor

	bool m_is_buzi;

/*
//==== »нтенсивность источника пол¤
double	m_Source;
//==== »ндекс ¤чейки сетки, где расположено начало источника
int		m_SrcId1;
//==== »ндекс ¤чейки сетки, где расположен конец источника
int		m_SrcId2;
//==== «начение физического свойства ¤чейки сетки
//double	m_Prop;
//==== »ндексы начала и конца области со свойством m_Prop
int		m_PropId1;
int		m_PropId2;*/

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnClickedAnalitSave();
	void OnClickedAnalitString();

	// Generated message map functions
	//{{AFX_MSG(CParamDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnClickedApply();
	afx_msg void OnClickedApply2();
	afx_msg void OnClickedAddSignal1(){OnClickedAddSignal(1);}
	afx_msg void OnClickedAddSignal2(){OnClickedAddSignal(2);}
	afx_msg void OnClickedAddSignal(int n = 1);
	afx_msg void OnClickedSetTime();
	afx_msg void OnClickedSetTimeEnd();
	afx_msg void OnClickedCancel();
	afx_msg void OnButtonalpha();
	afx_msg void OnClickedOutWindow(void);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMDLG_H__7F099925_A667_46F9_9E5D_AEDE379EF5B7__INCLUDED_)
