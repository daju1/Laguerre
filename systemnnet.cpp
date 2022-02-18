#include "StdAfx.h"
//#include "vdouble.h"
#include "sequense.h"

#include "datenum.h"

#include "ymacrofun.h"
#include "systemnnet.h"

//конструктор
SystemNnet::SystemNnet(int _len)
{
	m_len=_len;
	m_lenPredict=0;

	m_nModelCount=0;
	m_nLagerCount=0;
	m_Gradient = 0;

	m_kh=1.0;
	m_khMax=1.5; 
	m_khMin=0.1; 
	
	m_kh1=0.2;
	m_kh2=0.9;
	m_kh3=1.3;

	m_kl=0.8;
	m_klMax=2.5; 
	m_klMin=0.1; 
	
	m_kl1=0.5;
	m_kl2=0.95;
	m_kl3=1.25;

	m_dEdY = vdouble(m_len);
	m_Y = vdouble(m_len);
	m_PredictedPart = 0;
}
void SystemNnet::Default()
{
	int i, j;
	for(i = 0; i < m_nLagerCount; i++)
	{
		m_vkl[i] = m_kl;
		for (j = 0; j < m_vLagerModel[i].m_ParamCount; j++)
			m_vLagerModel[i].m_vkp[j] = m_vLagerModel[i].m_kp;


	}
	for(i = 0; i < m_nModelCount; i++)
	{
		m_vkh[i] = m_kh;
		for (j = 0; j < m_vModel[i].m_ParamCount; j++)
			m_vModel[i].m_vkp[j] = m_vModel[i].m_kp;
	}
}
SystemNnet::SystemNnet(int _len, int _lenPredict)
{
	m_len = _len;
	m_lenPredict = _lenPredict;
	m_PredictedPart = (double)m_lenPredict/((double)m_len+(double)m_lenPredict);

	SystemNnet SN = SystemNnet(m_len + m_lenPredict);
	m_T = vdouble(m_len);
	m_t = vdouble(m_len);
	m_Y = vdouble(m_len);
	m_dEdY = vdouble(m_len);

	m_TPredict = vdouble(m_lenPredict);
	m_tPredict = vdouble(m_lenPredict);
	m_YPredict = vdouble(m_lenPredict);
	m_dEdY_Predict = vdouble(m_lenPredict);

	m_nModelCount=0;
	m_nLagerCount=0;
	m_Gradient = 0;

	m_kh=SN.m_kh;
	m_khMax=SN.m_khMax; 
	m_kh1=SN.m_kh1;
	m_kh2=SN.m_kh2;
	m_kh3=SN.m_kh3;

	m_kl=SN.m_kl;
	m_klMax=SN.m_klMax; 
	m_kl1=SN.m_kl1;
	m_kl2=SN.m_kl2;
	m_kl3=SN.m_kl3;

	SN.~SystemNnet();
}
SystemNnet::SystemNnet(TargetLoader& TL, const double _PredictedPart)
{
	
	m_PredictedPart = _PredictedPart;

	m_len=(int)(((double)TL.m_len)*(1-m_PredictedPart));
	m_lenPredict = TL.m_len - m_len;
	

	SystemNnet SN = SystemNnet(m_len);
	m_T = TL.m_T[sequense(0,m_len-1)];
	m_t = TL.m_t[sequense(0,m_len-1)] - TL.m_t[0];
	m_Y = vdouble(m_len);
	m_dEdY = m_T;

	m_TPredict = TL.m_T[sequense(m_len,TL.Length()-1)];
	m_tPredict = TL.m_t[sequense(m_len,TL.Length()-1)] - TL.m_t[0];
	m_YPredict = vdouble(m_lenPredict);
	m_dEdY_Predict = vdouble(m_lenPredict);

	m_nModelCount=0;
	m_nLagerCount=0;
	m_Gradient = 0;

	m_kh=SN.m_kh;
	m_khMax=SN.m_khMax; 
	m_kh1=SN.m_kh1;
	m_kh2=SN.m_kh2;
	m_kh3=SN.m_kh3;

	m_kl=SN.m_kl;
	m_klMax=SN.m_klMax; 
	m_kl1=SN.m_kl1;
	m_kl2=SN.m_kl2;
	m_kl3=SN.m_kl3;
}
SystemNnet::SystemNnet(vdouble& _t, vdouble& _T, const double _PredictedPart) // Конструктор по целевому сигналу
{
	m_PredictedPart = _PredictedPart;
	if (_t.Length() !=_T.Length())
	{
		fprintf(stderr,"Error of SystemNnet constructor: (_t.m_length !=_T.m_length)\n");
		return;
	}
	m_len=(int)(((double)_t.Length())*(1-m_PredictedPart));
	m_lenPredict = _t.Length() - m_len;
	

	SystemNnet SN = SystemNnet(m_len);
	m_T = _T[sequense(0,m_len-1)];
	m_t = _t[sequense(0,m_len-1)] - _t[0];
	m_Y = vdouble(m_len);
	m_dEdY = m_T;

	m_TPredict = _T[sequense(m_len, _t.Length()-1)];
	m_tPredict = _t[sequense(m_len, _t.Length()-1)] - _t[0];
	m_YPredict = vdouble(m_lenPredict);
	m_dEdY_Predict = vdouble(m_lenPredict);

	m_nModelCount=0;
	m_nLagerCount=0;
	m_Gradient = 0;

	m_kh=SN.m_kh;
	m_khMax=SN.m_khMax; 
	m_kh1=SN.m_kh1;
	m_kh2=SN.m_kh2;
	m_kh3=SN.m_kh3;

	m_kl=SN.m_kl;
	m_klMax=SN.m_klMax; 
	m_kl1=SN.m_kl1;
	m_kl2=SN.m_kl2;
	m_kl3=SN.m_kl3;


}
SystemNnet::SystemNnet(vdouble& _t, vdouble& _T, vdouble& _t_Predict, vdouble& _T_Predict) // Конструктор по целевому сигналу
{
	if (_t.Length() !=_T.Length())
	{
		fprintf(stderr,"Error of SystemNnet constructor: (_t.m_length !=_T.m_length)\n");
		return;
	}
	if (_t_Predict.Length() !=_T_Predict.Length())
	{
		fprintf(stderr,"Error of SystemNnet constructor: (_t.m_length !=_T.m_length)\n");
		return;
	}
	m_len=_t.Length();
	m_lenPredict = _t_Predict.Length();
	

	SystemNnet SN = SystemNnet(m_len);
	m_T = _T;
	m_t = _t;
	m_Y = vdouble(m_len);
	m_dEdY = m_T;

	m_TPredict = _T_Predict;
	m_tPredict = _t_Predict;
	m_YPredict = vdouble(m_lenPredict);
	m_dEdY_Predict = vdouble(m_lenPredict);

	m_nModelCount=0;
	m_nLagerCount=0;
	m_Gradient = 0;

	m_kh=SN.m_kh;
	m_khMax=SN.m_khMax; 
	m_kh1=SN.m_kh1;
	m_kh2=SN.m_kh2;
	m_kh3=SN.m_kh3;

	m_kl=SN.m_kl;
	m_klMax=SN.m_klMax; 
	m_kl1=SN.m_kl1;
	m_kl2=SN.m_kl2;
	m_kl3=SN.m_kl3;
}

//деструктор
SystemNnet::~SystemNnet()
{
	for (int q=0; q < m_nModelCount; q++ )
		m_vModel[q].~BaseModel();
}

void
SystemNnet::ErrorNnet()
{
	static double OldError;
	OldError = m_E;
	// ошибка сети
	m_E = m_dEdY.SquareSum()/m_len;
	m_Gradient = m_E - OldError;

	m_MaxAbs_dEdY = m_dEdY.MaxAbs();
	
	m_EPredict = m_dEdY_Predict.SquareSum()/m_lenPredict;

	m_MaxAbs_dEdY_Predict = m_dEdY_Predict.MaxAbs();
}

void
SystemNnet::SimulNnet()
{
	int q;
	m_Y.Resetting();//  обнуление выхода системы
	m_YPredict.Resetting();//  обнуление выхода системы
	PBM pbm;
	for(q=0;q<m_nModelCount;q++)
	{
		pbm = &(m_vModel[q]);
		pbm ->ModelSignal();//генерация сигнала каждой модели

		m_Y += (m_h[q] * (pbm->m_y));//суммирование
		m_YPredict += (m_h[q] * (pbm->m_yPredict));//суммирование
	}
	PLM plm;
	for(q=0;q<m_nLagerCount;q++)
	{
		plm = &(m_vLagerModel[q]);
		(plm->*plm->m_pLagerSignal)();//генерация сигнала каждой модели
		m_Y.SummingFrom(plm->m_i0, m_l[q] * (plm->m_y));//суммирование
		m_YPredict += (m_l[q] * (plm->m_yPredict));//суммирование
	}
	m_dEdY=(m_T - m_Y);
	m_dEdY_Predict=(m_TPredict - m_YPredict);
}

void
SystemNnet::SimulNnet1(int _LagerNumber)
{
	int q;
	m_Y.Resetting();//  обнуление выхода системы
	m_YPredict.Resetting();//  обнуление выхода системы
	PBM pbm;

	for(q=0;q<m_nModelCount;q++)
	{
		pbm = &(m_vModel[q]);
		pbm ->ModelSignal();//генерация сигнала каждой модели

		m_Y += (m_h[q] * (pbm->m_y));//суммирование
		m_YPredict += (m_h[q] * (pbm->m_yPredict));//суммирование
	}
	PLM plm;
	plm = &(m_vLagerModel[q]);
		(plm->*plm->m_pLagerSignal)();//генерация сигнала модели
	for(q=0;q<m_nLagerCount;q++)
	{
		plm = &(m_vLagerModel[q]);
		m_Y.SummingFrom(plm->m_i0, m_l[q] * (plm->m_y));//суммирование
		m_YPredict += m_l[q] * (plm->m_yPredict);//суммирование
	}
	m_dEdY=(m_T - m_Y);
	m_dEdY_Predict=(m_TPredict - m_YPredict);

}
void SystemNnet::SimulNnetLager(int _LagerNumber)
{
	// Ускоренній вариант
	int q = _LagerNumber;
	PLM plm;
	plm = &(m_vLagerModel[q]);
	m_Y.SummingFrom(plm->m_i0, - m_l[q] * (plm->m_y));// - суммирование
	m_YPredict -= m_l[q] * (plm->m_yPredict);// - суммирование

	(plm->*plm->m_pLagerSignal)();//генерация сигнала модели

	m_Y.SummingFrom(plm->m_i0, m_l[q] * (plm->m_y));//суммирование
	m_YPredict += (m_l[q] * (plm->m_yPredict));//суммирование

	m_dEdY = m_T - m_Y;
	m_dEdY_Predict = m_TPredict - m_YPredict;
}
void SystemNnet::SimulNnetLager(int _LagerNumber, double old_h)
{
	// Ускоренній вариант
	int q = _LagerNumber;
	PLM plm;
	plm = &(m_vLagerModel[q]);
	m_Y.SummingFrom(plm->m_i0, (m_l[q] - old_h) * (plm->m_y));// - суммирование
	m_YPredict += (m_l[q] - old_h) * (plm->m_yPredict);// - суммирование
	m_dEdY = m_T - m_Y;
	m_dEdY_Predict = m_TPredict - m_YPredict;
}

void SystemNnet::SimulNnetModel(int _ModelNumber)
{
	// Ускоренній вариант
	int q = _ModelNumber;
	PBM pbm;
	pbm = &(m_vModel[q]);
	m_Y -= m_h[q] * (pbm->m_y);// - суммирование
	m_YPredict -= m_h[q] * (pbm->m_yPredict);// - суммирование

	pbm->ModelSignal();//генерация сигнала модели

	m_Y += m_h[q] * (pbm->m_y);//суммирование
	m_YPredict += (m_h[q] * (pbm->m_yPredict));//суммирование

	m_dEdY = m_T - m_Y;
	m_dEdY_Predict = m_TPredict - m_YPredict;
}

void SystemNnet::SimulNnetModel(int _ModelNumber, double old_h)
{
	// Ускоренній вариант
	int q = _ModelNumber;
	PBM pbm;
	pbm = &(m_vModel[q]);

	m_Y += (m_h[q] - old_h) * (pbm->m_y);//суммирование
	m_YPredict += (m_h[q] - old_h) * (pbm->m_yPredict);//суммирование

	m_dEdY = m_T - m_Y;
	m_dEdY_Predict = m_TPredict - m_YPredict;
}
PBM SystemNnet::AddModel(int _type)
{
	m_nModelCount++;
	BaseModel bm = BaseModel(this, _type);
	// инициализация нового объекта модели
	bm.InitModel();
	m_vModel.push_back(bm);
	m_toTurn.push_back(true);

	m_h.push_back(1.0);
	m_vkh.push_back(m_kh);
	m_ModelGradient.push_back(0.0);
	m_ModelEffect.push_back(0.0);

	PBM pBM = &m_vModel.End();
	return pBM;
}

int SystemNnet::LagerInitialization(int i0, LagerStruct& lgstr, int flag_of_Inf, CString& sNumDen, CString& sAnaliticEquation, CString& sRoots)
{
	CString s;
	sAnaliticEquation = "\n\nLager Initialization:\n";

	PLM pLM;
	int type, ParamCount;
	double h;
	vdouble Q, koef, param;
	Vector<vdouble> koefs;
	Q = m_dEdY.LagerQuotients(i0, m_t,lgstr, flag_of_Inf, koefs, sNumDen, sRoots);
	int N_lagers = koefs.Size();

	for (int iLag = 0; iLag < N_lagers; iLag++)
	{

		koef = koefs[iLag];
		if (koef.Length() == 4)
		{
			// koef[0] = xk*2.0;  // коэффициент перед косинусом
			// koef[1] = - yk*2.0; // отрицательный коэффициент перед синусом
			// koef[2] = x; // коэффициент показателя экспоненты (Real part of root)
			// koef[3] = y; // круговая частота (Imag part of root)
			type = 3;
			ParamCount = 3;
			param = vdouble(3);
			h = sqrt(koef[0] * koef[0] + koef[1] * koef[1]);
			param[0] = koef[2];
			param[1] = koef[3];
			param[2] = atan2( koef[0] , koef[1]);
			if (param[2] > 0)
			{
				s.Format("%g * exp(%g * t) * sin(%g * t + %g)\n", h, param[0], param[1], param[2]);
			}
			if (param[2] < 0)
			{
				s.Format("%g * exp(%g * t) * sin(%g * t - %g)\n", h, param[0], param[1], fabs(param[2]));
			}
			if (param[2] == 0)
			{
				s.Format("%g * exp(%g * t) * sin(%g * t)\n", h, param[0], param[1]);
			}
			sAnaliticEquation += s;
		}
		if (koef.Length() == 2)
		{
			// koef[0] = xk;// коэффициент перед экспонентой
			// koef[1] = x;// действительный корень
			type = 1;
			ParamCount = 1;
			param = vdouble(1);
			h = koef[0];
			param[0] = koef[1];

			s.Format("%g * exp(%g * t)\n", h, param[0]);
			sAnaliticEquation += s;
		}
		pLM = AddLager(i0, type, ParamCount, h);
		pLM->m_par = param;
	}
	SimulNnet();
	ErrorNnet();
	lgstr.error = m_E;
/*	fprintf(stderr, "(m_dEdY * m_dEdY).dispWithIndex();");
	(m_dEdY * m_dEdY).dispWithIndex();
	fprintf(stderr, "m_dEdY.CumMeanSquareSumFrom(0).dispWithIndex();");
	m_dEdY.CumMeanSquareSumFrom(0).dispWithIndex();
//	fprintf(stderr, "m_dEdY.CumMeanSquareSumFrom(0).DiffVector().dispWithIndex();");
//	m_dEdY.CumMeanSquareSumFrom(0).DiffVector().dispWithIndex();
	fprintf(stderr, " sqrt(m_E) = %g\n", sqrt(m_E));*/
	return 0;
}

PLM SystemNnet::AddLager(int i0, int type, int ParamCount, double h)
{
	m_nLagerCount++;
	LagerModel bm = LagerModel(this, i0, type, ParamCount);
	// инициализация нового объекта модели
	m_vLagerModel.push_back(bm);
	m_toTurnLager.push_back(true);

	m_l.push_back(h);
	m_vkl.push_back(m_kl);
	m_LagerGradient.push_back(0.0);
	m_LagerEffect.push_back(0.0);

	PLM pLM = &m_vLagerModel.End();
	return pLM;
}
void SystemNnet::DeleteModels(Vector<bool>& vbl)
{
	int q;
	if (m_nModelCount != vbl.Size())
	{
		fprintf(stderr,"Error using SystemNnet::DeleteModels(Vector<bool>& vbl):\n");
		fprintf(stderr,"Size of input bool Vector must be equial to m_nModelCount\n");
		return;
	}
	for (q = 0; q < m_nModelCount; q++)
	{
		if(vbl[q])
			m_vModel[q].~BaseModel();
	}

	m_nModelCount -= Find(vbl).Size();

	m_vModel.DeleteElements(vbl);
	m_toTurn.DeleteElements(vbl);

	m_h.DeleteElements(vbl);
	m_vkh.DeleteElements(vbl);
	m_ModelGradient.DeleteElements(vbl);
	m_ModelEffect.DeleteElements(vbl);
	// номер создаваемого объекта модели в сети
	for (q = 0; q < m_nModelCount; q++)
		m_vModel[q].m_q = q;
	return;
}

void SystemNnet::DeleteAll()
{
	int q;
	for (q = 0; q < m_nLagerCount; q++)
		m_vLagerModel[q].~LagerModel();
	m_nLagerCount = 0;

	m_vLagerModel.DeleteAll();
	m_toTurnLager.DeleteAll();

	m_l.DeleteAll();
	m_vkl.DeleteAll();
	m_LagerGradient.DeleteAll();
	m_LagerEffect.DeleteAll();

	for (q = 0; q < m_nModelCount; q++)
			m_vModel[q].~BaseModel();
	m_nModelCount = 0;

	m_vModel.DeleteAll();
	m_toTurn.DeleteAll();

	m_h.DeleteAll();
	m_vkh.DeleteAll();
	m_ModelGradient.DeleteAll();
	m_ModelEffect.DeleteAll();
}
void SystemNnet::DeleteLagers(Vector<bool>& vbl)
{
	int q;
	if (m_nLagerCount != vbl.Size())
	{
		fprintf(stderr,"Error using SystemNnet::DeleteLagers(Vector<bool>& vbl):\n");
		fprintf(stderr,"Size of input bool Vector must be equial to m_nLagerCount\n");
		return;
	}
	for (int q = 0; q < m_nLagerCount; q++)
	{
		if(vbl[q])
			m_vLagerModel[q].~LagerModel();
	}

	m_nLagerCount -= Find(vbl).Size();

	m_vLagerModel.DeleteElements(vbl);
	m_toTurnLager.DeleteElements(vbl);

	m_l.DeleteElements(vbl);
	m_vkl.DeleteElements(vbl);
	m_LagerGradient.DeleteElements(vbl);
	m_LagerEffect.DeleteElements(vbl);
	// номер создаваемого объекта модели в сети
	for (q = 0; q < m_nLagerCount; q++)
		m_vLagerModel[q].m_q = q;
	return;
}


void
SystemNnet::TurnNnet(bool toTurnAllParam)
{
	int q;
	// Определение тех параметров, настройка по которым имеет высокую эффективность
//	Vector<bool> m_toTurn(m_nModelCount), m_toTurnLager(m_nLagerCount);// to SystemNnet
	if (toTurnAllParam)
	{
		for(q=0; q<m_nModelCount; q++)
		{
			m_toTurn[q] = true;
		}
		for(q=0; q<m_nLagerCount; q++)
		{
			m_toTurnLager[q] = true;
		}
	}
	else
	{
		m_toTurn = m_ModelGradient < 0.5*m_ModelGradient.Mean();
		m_toTurnLager = m_LagerGradient < 0.5*m_LagerGradient.Mean();
	}
	double dEdh;
	double d2Edh,
		ModelGradient,LagerGradient,
		dh, dl, old_h;
	//настройка каждой модели в отдельности
	if (toTurnAllParam)
	{
		for(q=0; q<m_nModelCount; q++)
			m_vModel[q].TurnModel(true);
		for(q=0; q<m_nLagerCount; q++)
			m_vLagerModel[q].TurnLager(true);

	}
	else
	{
		for(q=0; q<m_nModelCount; q++)
			if (m_toTurn[q])
				m_vModel[q].TurnModel(false);
		for(q=0; q<m_nLagerCount; q++)
			if (m_toTurnLager[q])
				m_vLagerModel[q].TurnLager(false);
	}
	// ошибки сети по весам
	for(q=0; q<m_nModelCount; q++)
	{
		if (m_toTurn[q])
		{
			dEdh = m_dEdY.ScalarProduct(m_vModel[q].m_y);
			d2Edh = -(m_vModel[q].m_y.SquareSum());
			// настройка весов 
			if(d2Edh != 0)
				dh = m_vkh[q] * dEdh / d2Edh;
			else
				dh = 0.1 * m_vkh[q] * dEdh;
			old_h = m_h[q];
			m_h[q] -= dh;
			SimulNnetModel(q, old_h); //  основная генерация сигнала
//			SimulNnet();
			ModelGradient = m_dEdY.SquareSum()/m_len - m_E;

		
			if (ModelGradient > 0)
			{
				old_h = m_h[q];
				m_h[q] += dh;
				m_vkh[q] *= m_kh1; //0.5
				SimulNnetModel(q, old_h); // повторная генерация сигнала, поскольку основная генерация сигнала производилась с ошибочными параметрами
//				SimulNnet();
			}
			else 
			{
				if (ModelGradient < m_ModelGradient.Min() )
					m_vkh[q] *= m_kh3;//1.1
				if (ModelGradient > m_ModelGradient.Max() )
					m_vkh[q] *= m_kh2;//0.9
				m_ModelGradient[q] = ModelGradient;
			}
			if (m_vkh[q] < m_khMin)
				m_vkh[q] = m_khMin;
			if (m_vkh[q] > m_khMax)
				m_vkh[q] = m_khMax;

		}
	}
	// ошибки сети по весам Lager
	for(q=0; q<m_nLagerCount; q++)
	{
		if (m_toTurnLager[q])
		{
			dEdh = m_dEdY.ScalarProductFrom(m_vLagerModel[q].m_i0, m_vLagerModel[q].m_y);
			d2Edh = -(m_vLagerModel[q].m_y.SquareSum());
			// настройка весов 
			if(d2Edh != 0)
				dl = m_vkl[q] * dEdh / d2Edh;
			else
				dl = 0.1 * m_vkh[q] * dEdh;
			old_h = m_l[q];
			m_l[q] -= dl;
			SimulNnetLager(q, old_h); //  основная генерация сигнала
//			SimulNnet();
			LagerGradient = m_dEdY.SquareSum()/m_len - m_E;

		
			if (LagerGradient > 0)
			{
				old_h = m_l[q];
				m_l[q] += dl;
				m_vkl[q] *= m_kl1; //0.5
				SimulNnetLager(q,old_h); // повторная генерация сигнала, поскольку основная генерация сигнала производилась с ошибочными параметрами
//				SimulNnet();
			}
			else 
			{
				if (LagerGradient < m_LagerGradient.Min() )
					m_vkl[q] *= m_kl3;//1.1
				if (LagerGradient > m_LagerGradient.Max() )
					m_vkl[q] *= m_kl2;//0.9
				m_LagerGradient[q] = LagerGradient;
			}
			if (m_vkl[q] < m_klMin)
				m_vkl[q] = m_klMin;
			if (m_vkl[q] > m_klMax)
				m_vkl[q] = m_klMax;

		}
	}
}

TargetLoader::TargetLoader(const char * filename)
{
	m_T = vdouble();
	m_t = vdouble();
	
	FILE *stream;
	const int n=64; // length of buffer string line
	char szBuff[n]; // buffer string line
	
	char str_day[3];   int day;
	char str_month[3]; int month;
	char str_year[5];  int year;

	char str_hour[3];  int hour;
	char str_min[3];   int min;
	char str_sec[3];   int sec;

	double Time;
	double bid; 
	double ask;

	if ((stream = fopen(filename,"rt")) == NULL)
	{
		fprintf(stderr,"Cannot open input file.\n");
	}

	while (!feof(stream))
	{
		fgets(szBuff,n,stream);
		sscanf(szBuff,"%*1s %2s %*1s %2s %*1s %4s %2s %*1s %2s %*1s %2s %*s %*s %lf %lf %*s",
			str_day, str_month, str_year,
			str_hour, str_min, str_sec,
			&bid, &ask);
		day = atoi(str_day);
		month = atoi(str_month);
		year = atoi(str_year);
		hour = atoi(str_hour);
		min = atoi(str_min);
		sec = atoi(str_sec);

		Time = datenum(year,month,day,hour,min,sec);

		m_t.push_back(Time);

		m_T.push_back(bid);
	}
	fclose(stream);
	m_t.DeleteEnd();
	m_T.DeleteEnd();
	m_len = m_t.Length();
	fprintf(stderr,"The file is scanned successfully.\n");
}


void SystemNnet::AddInitGarmonicModels(int maxGarmonicOrder)
{
/*	vdouble A, fi, omega;
	m_T.FourierTransform(m_t,omega,A,fi);

	vdouble LocMaxA;
	Vector<int> LocMaxIndexes;
	int q=1;
	do 
	{
		A.LocalMaximums(q,LocMaxA, LocMaxIndexes);
		q++;
	}
	while (LocMaxA.Length() > 5 && q < A.Length()/2 - 1);
	
	fprintf(stderr,  "LocMaxA.disp() = ");
	LocMaxA.disp();

	vdouble InitOmegaValues, InitFiValues;
	InitOmegaValues = omega.Select(LocMaxIndexes);
	InitFiValues = fi.Select(LocMaxIndexes);
//////////////////////
	double T = m_t.End() - m_t[0];
	double omega0 = PI/T;
	InitOmegaValues.push_back(0.9*omega0);
	InitOmegaValues.push_back(omega0);
	InitFiValues.push_back(0.0);
	InitFiValues.push_back(0.0);
	vdouble InitHValues = LocMaxA;
	InitHValues.push_back(1.0);
	InitHValues.push_back(1.0);
//	InitOmegaValues += 100.0;
///////////////////////

	fprintf(stderr,  "InitOmegaValues.disp() = ");
	InitOmegaValues.disp();

	vdouble par;
	PBM pBM;
	int GarmonicCount = InitHValues.Length();

	fprintf(stderr,  " GarmonicCount = %i\n", GarmonicCount);
	double k;
	k=1.0;

	TrainParam tp;
	tp.epochs = 50;
	tp.goalE = 0.00001;
	tp.goalQ = 0.00001;
	tp.min_grad = 0.000001;
	tp.show = 1;
	tp.full_turn = 5;

	if (GarmonicCount > 0 && maxGarmonicOrder >= 1)
	{
		par = vdouble(2);
		for( int q1 = 0; q1 < GarmonicCount; q1++)
		{
			
			pBM = AddModel(COS_GARMONIC_MODEL);
			par[0] = InitOmegaValues[q1];
			par[1] = InitFiValues[q1];
			pBM->m_par = par;
			m_h[m_h.Length()-1]=k*InitHValues[q1];
		}
	}
//	Train(tp);
//	Train(tp, false);


//	m_h /=m_nModelCount;

	fprintf(stderr,  "m_nModelCount = %i\n", m_nModelCount);
	SimulNnet();
	TurnNnet();
	ModelEffect();
//	DeleteModels(m_ModelEffect < 0);
	TurnNnet();
	fprintf(stderr,  "m_nModelCount = %i\n", m_nModelCount);
/*
	ModelEffect();
	DeleteModels( m_ModelEffect < 
		(m_ModelEffect.Mean() - 0.55 * m_ModelEffect.Root_mean_square_Dismissal()));
	fprintf(stderr,  "m_nModelCount" << m_nModelCount << endl;
*/
}
/*
void SystemNnet::AddInitModels(int maxOrder)
{
	
	BaseModel *pBM;

	TrainParam tp;
	tp.epochs = 100;
	tp.goalE = 0.00001;
	tp.goalQ = 0.0001;
	tp.min_grad = 0.00001;
	tp.show = 100;


	pBM = AddModel(LINEAR_MODEL);
	m_h[0] = m_T.Mean();
	pBM->m_par[0] = 0;



	do
	{
		SimulNnet();
		ErrorNnet();

		fprintf(stderr,  "Error of linear Model = "  << sqrt(m_E) << endl;
		SystemNnet TempNnet(m_len, m_lenPredict);
		TempNnet.m_t = m_t;
		TempNnet.m_tPredict = m_tPredict;

		TempNnet.m_T = m_T - m_Y;
		TempNnet.m_TPredict = m_TPredict - m_YPredict;
		TempNnet.AddInitGarmonicModels(1);
		TempNnet.Train(tp);
		if (TempNnet.m_E < m_E)
//			AddModelsFrom(TempNnet);
		TempNnet.~SystemNnet();
	///	SimulNnet();
	//	ErrorNnet();

	}
	while (sqrt(m_E) > 0.0001 && m_nModelCount < 3);
	
}
*/
/*
void SystemNnet::AddInitGarmonicModel()
{
	
	vdouble InitOmegaValues, InitFiValues, InitHValues;
	vdouble A, fi, omega;
	PBM pBM;
	static vdouble InitOmegaUsed;

	do
	{
		m_T.FourierTransform(m_t,omega,A,fi);
		vdouble LocMaxA;
		Vector<int> LocMaxIndexes;
		int q=1;
		do 
		{
//			A.LocalMaximumsWithBorders(q,LocMaxA, LocMaxIndexes);
			A.LocalMaximums(q,LocMaxA, LocMaxIndexes);
			q++;
		}
		while (LocMaxA.Length() > 5 && q < (A.Length()-1)/2);
		fprintf(stderr,  "LocMaxA.disp() = ";
		LocMaxA.disp();

		InitOmegaValues = omega.Select(LocMaxIndexes);
		InitFiValues = fi.Select(LocMaxIndexes);
		InitHValues = LocMaxA;

		if (InitOmegaUsed.Length() == 0)
		{
//			indexes = LocMaxA.Max() == LocMaxA;
//			InitOmega = InitOmegaValues.Select(indexes)[0];
		}
		else
		{

		}

		double InitOmega = InitOmegaValues[0];
		double InitFi = InitFiValues[0];
//		double InitH = MaxA;

		InitOmegaUsed.push_back(InitOmega);
		//InitFiValues.push_back(InitFi);
		//InitHValues.push_back(InitH);
	
		pBM = AddModel(COS_GARMONIC_MODEL);
		pBM->m_par[0] = InitOmega;
		pBM->m_par[1] = InitFi;
//	m_h[m_h.Length()-1] = InitH;

	fprintf(stderr,  "Added COS Model InitOmega = " << InitOmega << endl;
	}
	while(false);
	
}
*/
void SystemNnet::Train(TrainParam& tp, CString& sNumDen, CString& sAnaliticEquation, CString& sRoots, bool toTurnAllParam)
{
	CString s;
	sAnaliticEquation = "\n\nLager Initialization:\n";
	sRoots = "\nRoots of denominator:\n";
	sNumDen = "";
	int Epoch = 0;

	int FullTurn = tp.full_turn;
	int ShowEpochs = tp.show;
	int MaxEpochs = tp.epochs;
	double MinError = tp.goalE,
		min_MaxAbs_dEdY = tp.goalQ,
		minGradient = tp.min_grad;

	bool Flag;
	SimulNnet();

	do
	{
		if (Epoch%FullTurn == 0 || toTurnAllParam) // полная настройка всех параметров во всех моделях
		{
			SimulNnet();
			TurnNnet(true);
			ErrorNnet();
		}
		else // настройка наиболее єффективных параметров в наиболее эффективных моделях
		{
			TurnNnet(false);
			ErrorNnet();
		}
		Epoch++;
		Flag = Epoch <= MaxEpochs && sqrt(m_E) > MinError && 
			m_MaxAbs_dEdY > min_MaxAbs_dEdY 
			&& ((sqrt(fabs(m_Gradient))>minGradient) || (m_Gradient > 0));
		/*if ((Epoch%ShowEpochs == 0 && Epoch != 0 ) || !Flag || Epoch == 0)
		{
			fprintf(stderr,  "Error = %g",   sqrt(m_E)); 
			if (m_lenPredict > 0)
				fprintf(stderr,  " PredictError = %g",   sqrt(m_EPredict)); 
			fprintf(stderr,  "\n MaxAbs_dEdY = %g",   m_MaxAbs_dEdY); 
			if (m_lenPredict > 0)
				fprintf(stderr,  " MaxAbs_dEdY_Predict = %g",  m_MaxAbs_dEdY_Predict);
			fprintf(stderr,  "\n Gradient = %g", sqrt(fabs(m_Gradient)));
			fprintf(stderr,  " Epoch = %i\n",  Epoch);
			fprintf(stderr,  "vdouble::m_szMemory = %i\n" , vdouble::m_szMemory );
			for (int iLag = 0; iLag < m_nLagerCount; iLag++)
			{
				vdouble param = m_vLagerModel[iLag].m_par;
				int type = m_vLagerModel[iLag].m_type;
				double h = m_l[iLag];
				if (type == 3)
				{
					if (param[2] > 0)
						fprintf(stderr,"%g * exp(%g * t) * sin(%g * t + %g)\n", h, param[0], param[1], param[2]);
					if (param[2] < 0)
						fprintf(stderr,"%g * exp(%g * t) * sin(%g * t - %g)\n", h, param[0], param[1], fabs(param[2]));
					if (param[2] == 0)
						fprintf(stderr,"%g * exp(%g * t) * sin(%g * t)\n", h, param[0], param[1]);
				}
				if (type == 1)
				{
					fprintf(stderr,"%g * exp(%g * t)\n", h, param[0]);
				}
			}
		}*/
	}
	while(Flag);
	//
	bool isRealRoots = false,
		isComplexRoots = false;
	int nRealRoots = 0,
		nComplexRoots = 0;
	for (int iLag = 0; iLag < m_nLagerCount; iLag++)
	{
		vdouble param = m_vLagerModel[iLag].m_par;
		int type = m_vLagerModel[iLag].m_type;
		double h = m_l[iLag];
		if (type == 3)
		{
			isComplexRoots = true;nComplexRoots++;
			if (param[2] > 0)
				s.Format("%g * exp(%g * t) * sin(%g * t + %g)\n", h, param[0], param[1], param[2]);
			if (param[2] < 0)
				s.Format("%g * exp(%g * t) * sin(%g * t - %g)\n", h, param[0], param[1], fabs(param[2]));
			if (param[2] == 0)
				s.Format("%g * exp(%g * t) * sin(%g * t)\n", h, param[0], param[1]);
			sAnaliticEquation += s;


		}
		if (type == 1)
		{
			isRealRoots = true;nRealRoots++;
			s.Format("%g * exp(%g * t)\n", h, param[0]);
			sAnaliticEquation += s;
		}
	}
	if (isRealRoots)
	{
		s.Format("Real roots(%i):\n", nRealRoots);
		sRoots += s;
		int j = 0;
		for (int iLag = 0; iLag < m_nLagerCount; iLag++)
		{
			vdouble param = m_vLagerModel[iLag].m_par;
			int type = m_vLagerModel[iLag].m_type;
			double h = m_l[iLag];
			if (type == 1)
			{
				s.Format( "N = %i:  %g\t\tabs = %g\n",j , param[0], fabs(param[0]));
				sRoots += s;
				j++;
			}
		}
	}
	if (isComplexRoots)
	{
		s.Format("Complex roots(%i):\n", nComplexRoots);
		sRoots += s;
		int j = 0;
		for (int iLag = 0; iLag < m_nLagerCount; iLag++)
		{
			vdouble param = m_vLagerModel[iLag].m_par;
			int type = m_vLagerModel[iLag].m_type;
			double h = m_l[iLag];
			if (type == 3)
			{
				s.Format( "N = %i:  %g  + i * %g   \t   abs = %g\n",j , param[0], param[1], sqrt( param[0]*param[0] + param[1] * param[1]));
				sRoots += s;j++;
			}
		}
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

BaseModel::BaseModel(SystemNnet* _pNnet, int _type)
{
	// указатель на объект - родитель нейросети
	m_pNnet = _pNnet;
	// тип модели
	m_type = _type;
	// макроопределение числа настраиваемых параметров
	m_ParamCount = AllParamCount(_type);
	m_toTurn = Vector<bool>(m_ParamCount);
	// номер создаваемого объекта модели в сети
	m_q = (m_pNnet->m_nModelCount)-1;
	// выделение памяти для массива выхода модели
	m_y = vdouble(m_pNnet->m_len);
	m_yPredict = vdouble(m_pNnet->m_lenPredict);
	// массив настраиваемых параметров
	m_kpMax=1.5; 
	m_kpMin=0.1; 
	m_kp=1.0; 
	m_kp1=0.1;
	m_kp2=0.9;
	m_kp3=1.3;
	m_par = vdouble(m_ParamCount);

	m_ParamGradient = vdouble(m_ParamCount, 0.0);

	m_vkp = vdouble(m_ParamCount,m_kp);
	m_dydpar = vdouble(m_pNnet->m_len);
	m_d2ydpar = vdouble(m_pNnet->m_len);
}

BaseModel::~BaseModel()
{
}

void
BaseModel::InitModel()
{
	// инициализация параметров модели по умолчанию
	for(int npar=0;npar<m_ParamCount;npar++)
	{
		m_par(npar)=AllInitPar(m_type,npar,1);
	}

}

void
BaseModel::InitModel(int init)
{
	// инициализация параметров модели
	for(int npar=0;npar<m_ParamCount;npar++)
	{
		m_par(npar)=AllInitPar(m_type,npar,init);
	}

}


void
BaseModel::TurnModel(bool toTurnAllParam)
{
	int npar;
	// Определение тех параметров, настройка по которым имеет высокую эффективность
//	Vector<bool> m_toTurn;
	if (toTurnAllParam)
	{
		for(npar = 0; npar < m_ParamCount; npar++)
			m_toTurn[npar] = true;
	}
	else
	{
		m_toTurn = m_ParamGradient < m_ParamGradient.Mean();
	}
	// объявление массивов первой и второй производной
	// ошибки сети по настраиваемым параметрам
	double dEdpar;
	double d2Edpar;
	double ParamGradient,
		dpar;
	// указатель на весовой коэффициент данной модели
	static double h;
	h = (m_pNnet->m_h[m_q]);

	// инициализация нулями массивов первой и второй производной
	// ошибки сети по настраиваемым параметрам
	dEdpar = 0;
	d2Edpar = 0;
	// вычисление первой и второй производной ошибки
	// сети по всем настраиваемым параметрам
	for(npar=0;npar<m_ParamCount;npar++)
	{
		if (m_toTurn[npar]) // настройка данного параметра имеет высокую эффективность
		{
			ModelSignalDerivatives(npar);
		
			dEdpar = m_pNnet->m_dEdY.ScalarProduct(m_dydpar);
			d2Edpar = m_pNnet->m_dEdY.ScalarProduct(m_d2ydpar)
				- m_dydpar.SquareSum()*h;
	
		// настройка настраиваемых параметров
		//
			if(d2Edpar != 0)
				dpar = m_vkp[npar] * dEdpar / d2Edpar;
			else
				dpar -= 0.1 * m_vkp[npar] * dEdpar;

			m_par[npar] -= dpar;
			m_pNnet->SimulNnetModel(m_q);
//			m_pNnet->SimulNnet();
			ParamGradient = 
				(m_pNnet->m_dEdY).SquareSum()/m_pNnet->m_len - m_pNnet->m_E;
		
			if (ParamGradient > 0) // отмена настройки параметра
			{
				m_par[npar] += dpar;
				m_vkp[npar] *= m_kp1; //0.5
				m_pNnet->SimulNnetModel(m_q);
//				m_pNnet->SimulNnet();
			}
			else // перенастройка коэффициентов скорости настройки
			{
				if (ParamGradient < m_ParamGradient.Min() )
					m_vkp[npar] *= m_kp3;//1.1
				if (ParamGradient > m_ParamGradient.Max() )
					m_vkp[npar] *= m_kp2;//0.9
				m_ParamGradient[npar] = ParamGradient;
			}
			if (m_vkp[npar] < m_kpMin)
				m_vkp[npar] = m_kpMin;
			if (m_vkp[npar] > m_kpMax)
				m_vkp[npar] = m_kpMax;

		}
	};
//	m_par = m_par / m_par.End();
}




//////////////////////////////////////////////
///
////
///////////////////////////////////////////////


// определения 
// функции ModelSignal
//vdouble& 
void BaseModel::ModelSignal()
{
//	vdouble y;
	switch(m_type)
	{
	case 0: m_y = Y0(m_pNnet->m_t); m_yPredict = Y0(m_pNnet->m_tPredict);break;
	case 1: m_y = Y1(m_pNnet->m_t); m_yPredict = Y1(m_pNnet->m_tPredict);break;
	case 2: m_y = Y2(m_pNnet->m_t); m_yPredict = Y2(m_pNnet->m_tPredict);break;
	case 3: m_y = Y3(m_pNnet->m_t); m_yPredict = Y3(m_pNnet->m_tPredict);break;
	}
//	return y;
}

// определение 
// функции ModelSignalFirstDerivative
void BaseModel::ModelSignalDerivatives(int npar)
{
//	vdouble dydpar;
	switch(m_type)
	{
	case 0 :
		switch(npar)
		{
			case 0: 
				m_dydpar = DY0DPAR0(m_pNnet->m_t) ;
				m_d2ydpar = DY0DPAR0(m_pNnet->m_t) ;
				break;
		} break;
	case 1 :
		switch(npar)
		{
			case 0: 
				m_dydpar = DY1DPAR0(m_pNnet->m_t) ;
				m_d2ydpar = DY1DPAR0(m_pNnet->m_t) ;
				break;
			case 1:
				m_dydpar = DY1DPAR1(m_pNnet->m_t) ;
				m_d2ydpar = DY1DPAR1(m_pNnet->m_t) ;
				break;
			case 2: 
				m_dydpar = DY1DPAR2(m_pNnet->m_t) ;
				m_d2ydpar = DY1DPAR2(m_pNnet->m_t) ;
				break;
		} break;
	case 2 :
		switch(npar)
		{
			case 0: 
				m_dydpar = DY2DPAR0(m_pNnet->m_t) ;
				m_d2ydpar = DY2DPAR0(m_pNnet->m_t) ;
				break;
			case 1: 
				m_dydpar = DY2DPAR1(m_pNnet->m_t) ;
				m_d2ydpar = DY2DPAR1(m_pNnet->m_t) ;
				break;
			case 2: 
				m_dydpar = DY2DPAR2(m_pNnet->m_t) ;
				m_d2ydpar = DY2DPAR2(m_pNnet->m_t) ;
				break;
		} break;
	case 3 :
		switch(npar)
		{
			case 0: 
				m_dydpar = DY3DPAR0(m_pNnet->m_t) ;
				m_d2ydpar = DY3DPAR0(m_pNnet->m_t) ;
				break;
			case 1: 
				m_dydpar = DY3DPAR1(m_pNnet->m_t) ;
				m_d2ydpar = DY3DPAR1(m_pNnet->m_t) ;
				break;
		} break;
	}
//	return dydpar;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
LagerModel::LagerModel(SystemNnet* _pNnet, int _i0, int _type, int _ParamCount)
{
	// указатель на объект - родитель нейросети
	m_pNnet = _pNnet;
	// 
	m_i0  = _i0;
	//
	m_len = m_pNnet->m_len - m_i0;
	m_lenPredict = m_pNnet->m_lenPredict;
	//
	m_t0 = m_pNnet->m_t[m_i0];
	// тип модели
	m_type = _type;
	// макроопределение числа настраиваемых параметров
	m_ParamCount = _ParamCount;
	m_toTurn = Vector<bool>(m_ParamCount);
	// номер создаваемого объекта модели в сети
	m_q = (m_pNnet->m_nLagerCount)-1;
	//
	m_t = m_pNnet->m_t[sequense(m_i0, m_pNnet->m_len - 1)] - m_t0;
	m_tPredict = m_pNnet->m_tPredict - m_t0;
	//
	m_pt = m_t.pD;
	m_ptPredict = m_tPredict.pD;
	


	// выделение памяти для массива выхода модели
	m_y = vdouble(m_len);
	m_yPredict = vdouble(m_pNnet->m_lenPredict);
	//
	m_py = m_y.pD;
	m_pyPredict = m_yPredict.pD;
	// массив настраиваемых параметров
	m_kpMax = 2.5; 
	m_kpMin = 0.3; 
	m_kp=1.0; 
	m_kp1=0.5;
	m_kp2=0.95;
	m_kp3=1.25;
	m_par = vdouble(m_ParamCount);

	m_ParamGradient = vdouble(m_ParamCount, 0.0);

	m_vkp = vdouble(m_ParamCount,m_kp);
	m_dydpar = vdouble(m_len);
	m_d2ydpar = vdouble(m_len);
	
	if(m_type == 1 )
	{
		m_pLagerSignal = &LagerModel::LagerSignal1;
		m_pLagerSignalDerivatives = &LagerModel::LagerSignalDerivatives1;
	}
	if(m_type == 3 )
	{
		m_pLagerSignal = &LagerModel::LagerSignal3;
		m_pLagerSignalDerivatives = &LagerModel::LagerSignalDerivatives3;
	}
}

LagerModel::~LagerModel()
{
}

void
LagerModel::InitLager()
{
}

void
LagerModel::InitLager(int init)
{
}
void
LagerModel::TurnLager(bool toTurnAllParam)
{
	int npar;
	// Определение тех параметров, настройка по которым имеет высокую эффективность
	if (toTurnAllParam)
	{
		for(npar = 0; npar < m_ParamCount; npar++)
			m_toTurn[npar] = true;
	}
	else
	{
		m_toTurn = m_ParamGradient < m_ParamGradient.Mean();
	}
	// объявление массивов первой и второй производной
	// ошибки сети по настраиваемым параметрам
	double dEdpar;
	double d2Edpar;
	double ParamGradient,
		dpar;
	// указатель на весовой коэффициент данной модели
	static double h;
	h = (m_pNnet->m_l[m_q]);

	// инициализация нулями массивов первой и второй производной
	// ошибки сети по настраиваемым параметрам
	dEdpar = 0;
	d2Edpar = 0;
	// вычисление первой и второй производной ошибки
	// сети по всем настраиваемым параметрам
	for(npar=0;npar<m_ParamCount;npar++)
	{
		if (m_toTurn[npar]) // настройка данного параметра имеет высокую эффективность
		{
			(this->*m_pLagerSignalDerivatives)(npar);
			
			dEdpar = m_pNnet->m_dEdY.ScalarProductFrom(m_i0, m_dydpar);
			d2Edpar = m_pNnet->m_dEdY.ScalarProductFrom(m_i0, m_d2ydpar)
				- m_dydpar.SquareSum()*h;
	
			// настройка настраиваемых параметров
			//
			if(d2Edpar != 0)
				dpar = m_vkp[npar] * dEdpar / d2Edpar;
			else
				dpar -= 0.1 * m_vkp[npar] * dEdpar;

			m_par[npar] -= dpar;
			m_pNnet->SimulNnetLager(m_q);
//			m_pNnet->SimulNnet();
			ParamGradient = 
				(m_pNnet->m_dEdY).SquareSum()/m_pNnet->m_len - m_pNnet->m_E;
			if (ParamGradient > 0) // отмена настройки параметра
			{
				int mw = 0;
				do
				{
					mw++;
					m_par[npar] += dpar;
					m_vkp[npar] *= m_kp1; //0.5
					m_pNnet->SimulNnetLager(m_q);
	//				m_pNnet->SimulNnet();
					// настройка настраиваемых параметров
					if(d2Edpar != 0)
						dpar = m_vkp[npar] * dEdpar / d2Edpar;
					else
						dpar -= 0.1 * m_vkp[npar] * dEdpar;

					m_par[npar] -= dpar;
					m_pNnet->SimulNnetLager(m_q);
					ParamGradient = 
						(m_pNnet->m_dEdY).SquareSum()/m_pNnet->m_len - m_pNnet->m_E;
				}
				while (ParamGradient > 0  && mw < 10);
			}
		
			if (ParamGradient > 0) // отмена настройки параметра
			{
				m_par[npar] += dpar;
				m_vkp[npar] *= m_kp1; //0.5
				m_pNnet->SimulNnetLager(m_q);
	//			m_pNnet->SimulNnet();
			}
			else // перенастройка коэффициентов скорости настройки
			{
				if (ParamGradient < m_ParamGradient.Min() )
					m_vkp[npar] *= m_kp3;//1.1
				if (ParamGradient > m_ParamGradient.Max() )
					m_vkp[npar] *= m_kp2;//0.9
				m_ParamGradient[npar] = ParamGradient;
			}
			if (m_vkp[npar] < m_kpMin)
				m_vkp[npar] = m_kpMin;
			if (m_vkp[npar] > m_kpMax)
				m_vkp[npar] = m_kpMax;
		}
	}
}
void LagerModel::LagerSignal1()
{
	int i;
	static double ti, par; 
	par = m_par[0];
	for(i = 0; i < m_len; i++)
	{
		ti = m_pt[i];
		*(m_py + i) = exp( par * ti);
	}
	for( i = 0; i < m_lenPredict; i++)
	{ 
		ti = m_ptPredict[i];
		*(m_pyPredict + i) = exp( par * ti);
	}
}
void LagerModel::LagerSignal3()
{
	int i;
	static double ti, par0, par1, par2;
	par0 = m_par[0];
	par1 = m_par[1];
	par2 = m_par[2];

	for(i = 0; i < m_len; i++)
	{
		ti = m_t[i];
		*(m_py + i) = exp( par0 * ti) * sin(par1 * ti + par2);
	}
	for(i = 0; i < m_lenPredict; i++)
	{
		ti = m_tPredict[i];
		*(m_pyPredict + i) = exp( par0 * ti) * sin(par1 * ti + par2);
	}
}

void LagerModel::LagerSignalDerivatives1(int npar)
{
	m_dydpar = m_t * m_y;
	m_d2ydpar = m_dydpar * m_t;
}
void LagerModel::LagerSignalDerivatives3(int npar)
{
	int i;
	static double ti, par0, par1, par2;
	par0 = m_par[0];
	par1 = m_par[1];
	par2 = m_par[2];
	switch (npar)
	{
	case 0:
		m_dydpar = m_y * m_t;
		m_d2ydpar = m_dydpar * m_t;
		break;
	case 1:
		for(i = 0; i < m_len; i++)
		{ 
			ti = m_t[i];
			m_dydpar[i] = exp( par0 * ti) * cos(par1 * ti + par2) * ti;
			m_dydpar[i] = - *(m_py + i) * ti * ti;
		}
		break;
	case 2:
		for(i = 0; i < m_len; i++)
		{ 
			ti = m_t[i];
			m_dydpar[i] = exp( par0 * ti) * cos(par1 * ti + par2);
			m_dydpar[i] = - *(m_py + i);
		}
		break;
	}
}

