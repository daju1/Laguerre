// systemnnet.h
#if !defined(_SYSTEMNNET_)
#define _SYSTEMNNET_


struct TrainParam // Структура параметров обучения нейросети
{
	int epochs;  // Максимальное число эпох
	double goalE; // Целевое значение среднеквадратичной ошибки
	double goalQ; //  Целевое значение максимальной точечной ошибки
	double min_grad; // Минимальный модуль градиента
	int show; // число эпох для вывода на экран результатов обучения
	int full_turn; // число эпох через которые производится полная настройка сети (всех параметров во всех моделях) 
//	double time; // Максимальное время обучения
};

class TargetLoader
{
	friend class SystemNnet;
	vdouble m_T,
		m_t;
	int m_len;
public:
	TargetLoader(const char * filename);
	int Length(){return m_len;} // Возвращает длину вектора

};


class SystemNnet;//неполное объявление класса BaseModel

class BaseModel
{

private:

public:
	int m_type;// тип объекта модели
	int m_ParamCount;// число настраиваемых параметрав
	SystemNnet* m_pNnet;//указатель на объект нейросети класса SystemNnet
	                    //включающий в себя данный объект класса BaseModel
	int m_q; // порядковый номер данной модели в системе
	vdouble m_y, // Вектор выхода модели
		m_par, // Вектор настраиваемых параметров
		m_vkp,// Вектор коэффициентов скорости настройки параметров
		m_dydpar,
		m_d2ydpar,
		m_ParamGradient,
		m_yPredict;
	double m_kp, 
		m_kp1, 
		m_kp2, 
		m_kp3, 
		m_kpMax,
		m_kpMin;//коэффициент скоровти настройки параметров
//функции-члены
	Vector<bool> m_toTurn;
	BaseModel(SystemNnet* _pNnet, int _type);//конструктор
	BaseModel(BaseModel& rhs)
	{
		m_ParamGradient = rhs.m_ParamGradient;
	
		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_toTurn = rhs.m_toTurn;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;
	}
	~BaseModel();//de структор
	void InitModel();//Инициализация параметров модели текущего типа набором начальных параметров № 1
	void InitModel(int init);//Инициализация параметров модели текущего типа набором начальных параметров № init
	void TurnModel(bool toTurnAllParam = true);//настройка параметров модели
	void ModelSignal();//симулирование (генерация) сигнала модели
	void ModelSignalDerivatives(int npar);
	BaseModel& operator=(BaseModel& rhs)
	{
		if (this == &rhs)
			return *this;
		m_ParamGradient = rhs.m_ParamGradient;
	
		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_toTurn = rhs.m_toTurn;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;
		return *this;

	}

};
typedef BaseModel* PBM;

class LagerModel
{

private:

public:
	int m_i0,
		m_len,
		m_lenPredict;
	int m_type;// тип объекта модели
	int m_ParamCount;// число настраиваемых параметрав
	SystemNnet* m_pNnet;//указатель на объект нейросети класса SystemNnet
	                    //включающий в себя данный объект класса BaseModel
	int m_q; // порядковый номер данной модели в системе
	vdouble m_t,
		m_tPredict,
		m_y, // Вектор выхода модели
		m_par, // Вектор настраиваемых параметров
		m_vkp,// Вектор коэффициентов скорости настройки параметров
		m_ParamGradient,
		m_yPredict,
		m_dydpar,
		m_d2ydpar;
	Vector<bool> m_toTurn;
	double m_t0,
		m_kp, 
		m_kp1, 
		m_kp2, 
		m_kp3, 
		m_kpMax,//коэффициент скоровти настройки параметров
		m_kpMin,
		*m_pt,
		*m_ptPredict,
		*m_py,
		*m_pyPredict;

		//функции-члены
	LagerModel(SystemNnet* _pNnet, int _i0, int _type, int _ParamCount);//конструктор
	LagerModel(LagerModel& rhs)
	{
		m_ParamGradient = rhs.m_ParamGradient;
		m_i0 = rhs.m_i0;
		m_len = rhs.m_len;
		m_lenPredict = rhs.m_lenPredict;
		m_t0 = rhs.m_t0;
			
		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_toTurn = rhs.m_toTurn;

		m_pLagerSignal = rhs.m_pLagerSignal;
		m_pLagerSignalDerivatives = rhs.m_pLagerSignalDerivatives;
	if(m_type == 1 )
	{
		void (LagerModel::*m_pLagerSignal) () = &LagerModel::LagerSignal1;
		void (LagerModel::*m_pLagerSignalDerivatives) (int npar) = &LagerModel::LagerSignalDerivatives1;
	}
	if(m_type == 3 )
	{
		void (LagerModel::*m_pLagerSignal) () = &LagerModel::LagerSignal3;
		void (LagerModel::*m_pLagerSignalDerivatives) (int npar) = &LagerModel::LagerSignalDerivatives3;
	}

		m_t = rhs.m_t;
		m_tPredict = rhs.m_tPredict;
		m_pt = m_t.pD;
		m_ptPredict = m_tPredict.pD;

		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_py = m_y.pD;
		m_pyPredict = m_yPredict.pD;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;

	}

	~LagerModel();//de структор
	void InitLager();//Инициализация параметров модели текущего типа набором начальных параметров № 1
	void InitLager(int init);//Инициализация параметров модели текущего типа набором начальных параметров № init
	void TurnLager(bool toTurnAllParam = true);//настройка параметров модели
	void LagerSignal1();//симулирование (генерация) сигнала модели
	void LagerSignal3();//симулирование (генерация) сигнала модели
	void (LagerModel::*m_pLagerSignal)();// Указатель на одну из функций генерации сигнала
	void LagerSignalDerivatives1(int npar);
	void LagerSignalDerivatives3(int npar);
	void (LagerModel::*m_pLagerSignalDerivatives)(int npar);//Указатель на одну из функций производной сигнала
	LagerModel& operator=(LagerModel& rhs)
	{
		if (this == &rhs)
			return *this;
		m_ParamGradient = rhs.m_ParamGradient;
		m_i0 = rhs.m_i0;
		m_len = rhs.m_len;
		m_lenPredict = rhs.m_lenPredict;
		m_t0 = rhs.m_t0;

		m_pLagerSignal = rhs.m_pLagerSignal;
		m_pLagerSignalDerivatives = rhs.m_pLagerSignalDerivatives;

		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_toTurn = rhs.m_toTurn;

		m_t = rhs.m_t;
		m_tPredict = rhs.m_tPredict;
		m_pt = m_t.pD;
		m_ptPredict = m_tPredict.pD;

		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_py = m_y.pD;
		m_pyPredict = m_yPredict.pD;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;
		return *this;
	}
};

typedef LagerModel* PLM;

class SystemNnet
{
public:
	int m_len;//длина шкалы времени, используемая в расчётах по настройке 
	int m_lenPredict;//длина шкалы времени, используемая для прогнозирования
	int m_nModelCount;//число моделей в системе
	int m_nLagerCount;//число моделей в системе
	
	vdouble m_vkl,
		m_vkh, // Вектор коэффициентов скорости настройки весов m_h
		m_t,// Шкала времени
		m_T,// Целевой вектор
		m_Y,// Выходной массив сети
		m_h,// Веса каждой модели в системе
		m_l,
		m_ModelGradient, // Вектор текущих градиентов для каждой модели
		m_LagerGradient,
		m_ModelEffect, // Вектор эффективности моделей
		m_LagerEffect,
		m_tPredict, // Шкала времени для прогноза
		m_TPredict, // Целевой вектор для прогноза
		m_YPredict, // Выходной массив сети для прогноза
		m_dEdY, // Текущий вектор ошибок по точкам
		m_dEdY_Predict; // Текущий вектор ошибок по точкам для прогноза

	Vector<BaseModel> m_vModel;// Массив объектов класса BaseModel
	Vector<LagerModel> m_vLagerModel;// Массив объектов класса BaseLager
	Vector<bool> m_toTurn, 
		m_toTurnLager;
	double m_E, // ошибка сети
		m_EPredict, // ошибка прогноза
		m_kh, // Начальный коэффициент скорости настройки весов m_h
		m_kl,
		m_kh1, // Множитель для элемента вектора m_vkh, если при подстройке веса ошибка увеличилась
		m_kl1,
		m_kh2, // Множитель для элемента вектора m_vkh, если при подстройке веса градиент модели по модулю минимален
		m_kl2,
		m_kh3, // Множитель для элемента вектора m_vkh, если при подстройке веса градиент модели по модулю максимален
		m_kl3,
		m_khMax, // Максимально допустимый коэффициент скорости настройки весов m_h
		m_klMax,
		m_khMin, // Максимально допустимый коэффициент скорости настройки весов m_h
		m_klMin,
		m_Gradient, // Градиент сети
		m_MaxAbs_dEdY, // Максимальная по модулю ошибка среди всех точек
		m_MaxAbs_dEdY_Predict, // Максимальная по модулю ошибка среди прогнозных точек
		m_PredictedPart; // Доля сигнала для прогноза: 0 <= m_PredictedPart < 1
		
	// конструктор
	SystemNnet(){} // 
	SystemNnet(int _len); // Простой конструктор
	SystemNnet(int _len, int _lenPredict); // Простой конструктор
	SystemNnet(TargetLoader& TL, const double _PredictedPart); // Конструктор по загруженному из файла целевому сигналу
	SystemNnet(vdouble& _t, vdouble& _T, const double _PredictedPart = 0.0); // Конструктор по целевому сигналу
	SystemNnet(vdouble& _t, vdouble& _T, vdouble& _t_Predict, vdouble& _T_Predict); // Конструктор по целевому сигналу
	~SystemNnet(); // Деструктор
	PBM AddModel(int _type); // добавление модели задаваемого типа в систему
	PLM AddLager(int _i0, int type, int ParamCount, double h);
	int LagerInitialization(int i0, LagerStruct& lgstr, int flag_of_Inf,
		CString& sNumDen, CString& sAnaliticEquation, CString& sRoots);
	void DeleteModels(Vector<bool>& vbl); // удаление моделей из системы
	void DeleteLagers(Vector<bool>& vbl);
	void DeleteAll();
	void Default();
	void ModelEffect(int modelNumber)
	{
		if ( modelNumber >= 0 && modelNumber < m_nModelCount)
			m_ModelEffect[modelNumber] = ( (m_dEdY + m_h[modelNumber] * m_vModel[modelNumber].m_y).SquareSum() -
				m_dEdY.SquareSum()) / m_len;
	}
	void LagerEffect(int lagerNumber)
	{
		if ( lagerNumber >= 0 && lagerNumber < m_nLagerCount)
			m_LagerEffect[lagerNumber] = ( (m_dEdY + m_l[lagerNumber] * m_vLagerModel[lagerNumber].m_y).SquareSum() -
				m_dEdY.SquareSum()) / m_len;
	}
	void ModelEffect()
	{
		ErrorNnet();
		vdouble dEdY = m_T - m_Y;
		for (int q = 0; q < m_nModelCount; q++)
			m_ModelEffect[q] = ((dEdY + m_h[q] * m_vModel[q].m_y).SquareSum() / m_len - m_E);
	}
	void LagerEffect()
	{
		ErrorNnet();
		vdouble dEdY = m_T - m_Y;
		for (int q = 0; q < m_nLagerCount; q++)
			m_LagerEffect[q] = ((dEdY + m_l[q] * m_vLagerModel[q].m_y).SquareSum() / m_len - m_E);
	}
//	void AddModelsFrom(SystemNnet& sn); // Добавление к текущей системе всех моделей из задаваемой системы
	void SimulNnet(); //симуляция (генерация) сигнала сети
	void SimulNnet1(int _LagerNumber); // to delete in future
	void SimulNnetLager(int _LagerNumber);// fast simul nnet after turning of one lager model
	void SimulNnetModel(int _ModelNumber); // fast simul nnet after turning of one model
	void SimulNnetLager(int _LagerNumber, double old_h);// fast simul nnet after turning of one lager model
	void SimulNnetModel(int _ModelNumber, double old_h); // fast simul nnet after turning of one model
	void ErrorNnet();//ошибка сети

	void TurnNnet(bool toTurnAllParam = true);//настройка сети
	void Train(TrainParam& tp, CString& sNumDen, CString& sAnaliticEquation, CString& sRoots, bool toTurnAllParam = true);

	void AddInitGarmonicModels(int maxGarmonicOrder);

	//void PaintNnet();//отрисовка выходного сигнала сети
//	void AddInitGarmonicModel();
///	void AddInitModels(int maxOrder);

};
#endif