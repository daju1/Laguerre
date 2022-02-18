//#include "StdAfx.h"

#if !defined(_VDOUBLE_)
#define _VDOUBLE_

#define PI		3.14159265358979323846
#define SD      8 // = (sizeof(double)) - проверить для данного компьютера
//#define COPY_CONSTR false
#define MEMORY_ERROR AfxMessageBox("Error using vdouble: not enough memory\n");return vdouble(0);
#define MEMORY_ERROR0 AfxMessageBox( "Error using vdouble: not enough memory\n");return;
#define MEMORY_ERROR2 AfxMessageBox( "Error using vdouble: not enough memory\n");return 1.0e300;

#define  DEBUGGING false
#include <cfloat>
#include "complex.h"

#define WF_HAAR							1
#define WF_DAUBECHIES					2
#define WF_SYMLETS						3
#define WF_COIFLETS						4
#define WF_BIORTOGONAL					5
#define WF_MY_BIORTOGONAL				6
#define WF_BIORTOGONAL_NONSTANDART		7
#define WF_DISCRETE_MEYER				8

//#include <exception>
struct LagerStruct;
class vdouble // Класс массива вещественных чисел double
{
	friend class CGraph;
	friend class LagerModel;
private:
	int m_length; // Длина вектора
	int m_dims;
	Vector<int> m_size;
	bool m_isgorizontal; // Флаг горизонтальности
	double *pD; // Указатель на одномерный массив вещественных 
			// чисел double
public:
	int idwt(vdouble &rh, vdouble &rg, vdouble &s, vdouble &d,
		vdouble& s_right, vdouble& d_right);
	int dwt(vdouble& t, vdouble& tau, vdouble&dh, vdouble& dg, vdouble&s, vdouble&d,
		vdouble& s_right, vdouble& d_right);
	int dwt(int j, vdouble &dh, vdouble &dg, vdouble &s, vdouble &d);
	int b_reconstructor(vdouble& b, vdouble& tt, vdouble& xx, double t0); 	// реконструкция коэффициентов числителя передаточной функции 
			// по  известному знаменателю (*this)  
			// а также по отклику на delta - импульс в момент t0

	void Rand(double minBorder, double maxBorder);
	double FirstLocalMinFrom(int j);
	double FirstLocalMaxFrom(int j);
	Vector<int> Size(){return m_size;}
	static unsigned int m_nConstructions; // Число раз выполнения конструкторов
	static unsigned int m_nDestructions; // Число раз выполнения деструкторов
	static size_t m_szMemory; // объём выделенной динамической памяти

	vdouble(); // Конструктор по умолчанию - создаёт объект вектора нулевой длины
	vdouble(vdouble& src); // Конструктор копирования - создаёт объект вектора нулевой длины
	vdouble(int _length);// Конструктор - создаёт объект вектора заданной длины
	vdouble(double array[], int _length/* = sizeof(array)/sizeof(double)*/);// Конструктор - создаёт объект по массиву чисел double
	vdouble(double& array, int _length/* = sizeof(array)/sizeof(double)*/);// Конструктор - создаёт объект по массиву чисел double
	vdouble(int _length, const double& ra);// Конструктор - создаёт объект вектора заданной длины, присваивая всем элементам задаваемое значение
	int Save(const char * filename);//
	int Write(const char * filename);//
	int Load(const char * filename);//

	vdouble(int rows, int cols); // Конструктор двумерной матрицы
	vdouble(int rows, int cols, int tabs); // Конструктор трёхмерной матрицы
	vdouble(Vector<int>& vsize); // Конструктор многомерной матрицы

	void resize(int _length);// 
	void resize(int _length, const double& ra);// 
	void resize(int rows, int cols); // 
	void resize(int rows, int cols, const double& ra); // двумерной матрицы
	void resize(int rows, int cols, int tabs); // 
	void resize(Vector<int>& vsize); // 

	virtual ~vdouble(); // Деструктор выполняет освобождение памяти

	friend vdouble inline zeros(int _length);// Создаёт вектор заданной длины из нулей
	friend vdouble inline ones(int _length); // Создаёт вектор заданной длины из единиц

	int Length(){return m_length;} // Возвращает длину вектора
	bool IsGorizontal(){return m_isgorizontal;} // Возвращает флаг горизонтальности
	
	void disp(); // Выводит значения элементов в консольное окно
	void dispWithIndex();
	void dispSquareMatrix();// Выводит значения элементов квадратной матрицы в консольное окно

	CString disp_str();
	CString dispMatrix_str();
	
	bool is_zeros(); // Истина, если все элементы - равны нулю
	bool is_zeros(const double& epsilon);// Истина, если модуль всех элементов не превышает epsilon

	double& operator[](int index); // Возвращает элемент по заданному индексу
	vdouble operator[](Vector<int>& ind); // Возвращает вектор-отрезок по заданныму массиву индексов
	vdouble operator()(Vector<int>& vrows, Vector<int>& vcols);
//	vdouble vdouble::operator[](Vector<Vector<int> >& ind); // Возвращает массив-отрезок по заданныму массиву индексов по каждой размерности
	double& operator()(int index); // Возвращает элемент по заданному индексу

	double& operator()(int row,int col); // Возвращает элемент двумерной матрицы по заданному индексу
	double& operator()(int row, int col, int tab); // Возвращает элемент трёхмерной матрицы по заданным индексам строки и столбца
	double& operator()(Vector<int>& indexes); // Возвращает элемент трёхмерной матрицы по заданным индексам строки и столбца

	vdouble& operator=(vdouble& rhs); // Перегруженный оператор присваивания
	vdouble& operator=(const double& ra);
	vdouble& SummingFrom(int i0, vdouble& rhs);// // Поэлементное суммирование с вектором аргумента с присваиванием начиная с указанного номера элемента
	vdouble& operator+=(vdouble& rhs);// Поэлементное суммирование с вектором аргумента с присваиванием
	vdouble& operator+=(const double& ra);
	
	vdouble& operator-=(vdouble& rhs);// Поэлементное вычитание вектора аргумента с присваиванием
	vdouble& operator-=(const double& ra);
	
	vdouble& operator*=(vdouble& rhs);// Поэлементное умножение на вектор аргумента с присваиванием
	vdouble& operator*=(const double& ra);
	
	vdouble& operator/=(vdouble& rhs);// Поэлементное деление на вектор аргумента с присваиванием
	vdouble& operator/=(const double& ra);// Деление на вещественное число с присваиванием

	friend vdouble inline operator+(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator+(const double& a, vdouble& ob2);
	friend vdouble inline operator+(vdouble& ob1, const double& a);

	friend vdouble inline operator-(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator-(const double& a, vdouble& ob2);
	friend vdouble inline operator-(vdouble& ob1, const double& a);

	friend vdouble inline operator^(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator^(const double& a, vdouble& ob2);
	friend vdouble inline operator^(vdouble& ob1, const double& a);
	
	friend vdouble inline pow(vdouble& ob1, vdouble& ob2);
	friend vdouble inline pow(const double& a, vdouble& ob2);
	friend vdouble inline pow(vdouble& ob1, const double& a);

	friend vdouble inline operator*(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator*(const double& a, vdouble& ob2);
	friend vdouble inline operator*(vdouble& ob1, const double& a);

	friend vdouble inline operator/(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator/(const double& a, vdouble& ob2);
	friend vdouble inline operator/(vdouble& ob1, const double& a);

	friend vdouble inline operator,(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator,(const double& a, vdouble& ob2);
	friend vdouble inline operator,(vdouble& ob1, const double& a);
	
	friend vdouble inline operator+(vdouble& ob);
	friend vdouble inline operator-(vdouble& ob);

	friend vdouble inline log(vdouble& ob);
	friend vdouble inline log10(vdouble& ob);
	friend vdouble inline abs(vdouble& ob);

	friend vdouble inline acos(vdouble& ob);
	friend vdouble inline asin(vdouble& ob);
	friend vdouble inline atan(vdouble& ob);
	friend vdouble inline atan2(vdouble& x, vdouble& y);

	friend vdouble inline cos(vdouble& ob);
	friend vdouble inline cosh(vdouble& ob);
	friend vdouble inline sin(vdouble& ob);
	friend vdouble inline sinh(vdouble& ob);
	friend vdouble inline tan(vdouble& ob);
	friend vdouble inline tanh(vdouble& ob);
	friend vdouble inline exp(vdouble& ob);
	friend vdouble inline sqrt(vdouble& ob);

	friend vdouble inline floor(vdouble& ob);
	friend vdouble inline ceil(vdouble& ob);

	friend Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator>(const double& a, vdouble& ob);
	friend Vector<bool> inline operator>(vdouble& ob, const double& a);

	friend Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator>=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator>=(vdouble& ob, const double& a);

	friend Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator<(const double& a, vdouble& ob);
	friend Vector<bool> inline operator<(vdouble& ob, const double& a);

	friend Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator<=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator<=(vdouble& ob, const double& a);

	friend Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator==(const double& a, vdouble& ob);
	friend Vector<bool> inline operator==(vdouble& ob, const double& a);

	friend Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator!=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator!=(vdouble& ob, const double& a);
	
	friend vdouble inline fliplr(vdouble& ob);

	friend void inline operator<<(vdouble& ob, const double& a);
	friend void inline operator>>(const double& a, vdouble& ob);

	friend void inline operator<<(CArchive& ar, vdouble& v);
	friend void inline operator>>(CArchive& ar, vdouble& v);

	friend vdouble inline conv(vdouble& v1, vdouble& v2);
	friend vdouble dsequence(double d0, double dstep, double dend);

	void Resetting(); // Обнуляет все элементы вектора
	double& End(); // Возвращает последний элемент вектора
	double& End(int n); // Возвращает n- ый элемент вектора с конца
		// n < 0
	vdouble Select(Vector<int>& indexes); // Возвращает новый вектор, выбирая элементы из данного вектора
	vdouble Select(Vector<bool>& vbl); // Возвращает новый вектор, выбирая элементы из данного вектора
	void LocalMaximums(vdouble& LocMax, Vector<int>& indexes); // Формирует вектор локальных максимумов и целочисленный вектор их индексов
	void LocalMaximums(int n, vdouble& LocMax, Vector<int>& indexes);// Формирует вектор локальных максимумов и целочисленный вектор их индексов
	void LocalMaximumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes);// Формирует вектор локальных максимумов и целочисленный вектор их индексов

	void LocalMinimums(vdouble& LocMin, Vector<int>& indexes);// Формирует вектор локальных минимумов и целочисленный вектор их индексов
	void LocalMinimums(int n, vdouble& LocMin, Vector<int>& indexes);// Формирует вектор локальных минимумов и целочисленный вектор их индексов
	void LocalMinimumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes);// Формирует вектор локальных максимумов и целочисленный вектор их индексов
	bool IsEndLocalMin(int n = 3);
	bool IsEndLocalMax(int n = 3);
	bool IsEndDecreaseDown(int n = 3);
	bool IsEndGrowUp(int n = 3);

	double Max(); // Возвращает мaксимальный элемент вектора
	double Min(); // Возвращает минимальный элемент вектора
	double MaxFrom(int j);
	double MinFrom(int j);
	double MaxAbs(); // Возвращает мaксимальный по абсолютному значению элемент вектора
	double MinAbs(); // Возвращает минимальный по абсолютному значению элемент вектора
	double Mean(); // Возврашает среднее арифметическое элементов вектора
	double Root_mean_square_Dismissal(); // Возврашает среднеквадратичное отклонение
	double Sum(); // Возврашает сумму элементов вектора
	double SquareSum(); // Возврашает сумму квадратов элементов вектора
	double SquareSumFrom(int i0); // Возврашает сумму квадратов элементов вектора, начиная с i0
	void push_back(double a);// Добавляет элемент в конец вектора
	void push_front(double a); // Добавляет элемент в начало вектора
	void DeleteEnd(); // Удаляет 1 последний элемент вектора
	void DeleteEnd(int n); // Удаляет n последних элементов вектора
	void DeleteElement(int index); // Удаляет index-ный элемент вектора
	void DeleteElements(Vector<bool>& vbl); // Удаляет элементы вектора
	void DeleteAll(); // Удаляет все элементы вектора

	vdouble CumMeanSquareSum();// Возврашает вектор кумулятивных квадратичных сумм, усреднённых по номеру элемента с извлечением корня
	vdouble CumMeanSquareSumFrom(int i0);// Возврашает вектор кумулятивных квадратичных сумм, усреднённых по номеру элемента с извлечением корня, начиная с i0
	vdouble CumSum(); // Возврашает вектор кумулятивных сумм
	vdouble CumMeanSum(); // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента
	vdouble CumMeanSumFrom(int i0); // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента, начиная с i0
	vdouble DiffVector();// Вектор конечных разностей (возвращает вектор на 1 короче)
	vdouble SumVector();//Вектор конечных сумм (сумм в соседних точках) - возвр. вект. на 1 короче
	double Trapz(vdouble& t); // Интегрирование методом трапеций на неравномерной временной сетке

	double ScalarProduct(vdouble& rhs); // Возвращает скалярное произведение на вектор в аргументе
	double ScalarProductFrom(int i0, vdouble& rhs); // Возвращает скалярное произведение на вектор в аргументе начиная с указанного номера элемента
	void FourierTransform(vdouble& t, vdouble& omega, vdouble& A, vdouble& fi ); // Фурье преобразование

	//============ Функции Лаггер - спектральных преобразований ============
	vdouble vLagerPolynom(int n);
	double LagerAlphaDeterm(int maxOrder, double tend, double EnergyPart = 0.95);
	double LagerAlphaDeterminition(double& tend, double& EnergyPart);
	vdouble LagerQuotients(int i0, vdouble& t, LagerStruct& lgstr, int flag_of_Inf, Vector<vdouble>& koefs, CString& sNumDen, CString& sRoots); // Вычисление коэффициентов Лагерра

	double LagerDeterminant(); // Вычисляет детерминант системы уравнений используя вектор коэффициентов Лагерра
	double LagerDeterminant(double alpha, double beta, vdouble& alphai, vdouble& flip_betai, vdouble& num, vdouble& den);// Вычисляет детерминант системы уравнений используя вектор коэффициентов Лагерра, а также коэффициенты передаточной ф-ции
	int InvLaplace(vdouble& num, vdouble& den, vdouble& t, vdouble& f_rekonstr, Vector<vdouble>& koefs, CString& sRoots); // Обратное преобразование Лаплапса для дроби полиномов

	//============ Функции Линейной алгебры ============
	vdouble MatrixProduct(vdouble& x);// Матричное произведение матрицы размера R x C на вертикальный вектор длиной C 
										// возвращает вектор длиной R
	vdouble MatrixWithMatrixProduct(vdouble& x); // Матричное произведение матрицы размера R1 x C1 на матрицу размера R2 x C2 причём C1 = R2
	vdouble TransponedMatrixProduct(vdouble& x);// Матричное произведение матрицы размера R x C на вертикальный вектор длиной R 
										// возвращает вектор длиной C
	vdouble VectorsToMatrixProduct(vdouble& gor); // Матричное произведение вертикального вектора длиной R
												// на горизонтальный вектор длиной C 
												// возвращает матрицу размером R x C
	vdouble TichonovOld(vdouble& b);
	vdouble Tichonov(vdouble& b); // Решение системы линейных уравнений методом регуляризации Тихонова
	int pinv(vdouble& pinvMatrix);// Псевдообращение матрицы
	vdouble LinearInterp(vdouble &t);
	vdouble LinearInterp();

	void EMA(vdouble& t, vdouble& tau, vdouble& ema, int nPoint); //Экспоненциальная скользящая средняя
	void NEMA(vdouble& t, vdouble& tau, 
		vdouble& ema,  vdouble& nema, int nPoints); //Нормированная Экспоненциальная скользящая средняя
	void Derivatives(vdouble& t, 
		double dt,
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		vdouble& tau, 
		vdouble& ma, vdouble& d1, vdouble& d2, 
		int nPoint, int interp_order, 
		bool uniform,
		bool isEnd = false, int nPredict = 0);// Первая и вторая производная
	void Derivative(vdouble& t, 
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		double& ma, double& d1, double& d2, // скользящая средняя и первая и вторая производная
		int interp_order);
	int Derivatives(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		vdouble& tDeriv, // вектор шкалы времени для производной - выходной параметр
		vdouble& DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
		int& i1, int& i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
		int interp_order, // порядок интерполяционного полинома
		int deriv_order, // порядок высшей производной
		int nPoints, // число точек временного окна
		double& qt, // коэффициент растяжки полиномов по оси времени - передаётся из прежде вызванной функции Derivatives
		bool uniform);// флаг равномерности временной сетки
	int Derivative(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		vdouble& tDeriv, // вектор шкалы времени для производной - выходной параметр
		vdouble& DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
		int& i1, int& i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
		int interp_order, // порядок интерполяционного полинома
		int deriv_order, // порядок высшей производной
		int nPoints, // число точек временного окна
		double& qt); // коэффициент растяжки полиномов по оси времени - передаётся из прежде вызванной функции Derivatives
	int diff_Wp(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
		vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		int denom_order, // порядок знаменателя передаточной функции
		int nPoints, // число точек временного окна для вычисления производной
		bool uniform, // флаг равномерной временной шкалы
		vdouble& denom, // коэффициенты знаменателя передаточной функции
		vdouble& num, // коэффициенты числителя передаточной функции
		vdouble& f_reconstr, // реконструированный сигнал
		double& er_deriv, // ошибка разложения сигнала по базису его производных
		double& er_reconstr);// ошибка реконтрукции сигнала
	double det(); // Детерминант
	void sls_det(vdouble& b, vdouble& x, double& _det, bool PrivateDesigion = false);//Решение линейной системы уравнений методом Гаусса
//	vdouble A(int j); // Алгебраическое дополнение

	vdouble PolynomDerivative();//Возвращает вектор полинома первой производной
	vdouble PolynomSumming(vdouble& v); // Суммирование полиномов
	void PolynomDivide(const vdouble& divisor, vdouble& quotient, vdouble& remainder);// Производит деление на полином
	int PolynomDivideIntoThree_member(double& b, double c);// Производит деление полинома на трёхчлен, в котором второй коэффициент b подлежит определению,
	int PolynomRootsSimple(vdouble& prs, vdouble& D);// Вычленяет кратные корни, получая полином с простыми корнями и соответствующий множитель
	int PolynomGreatestCommonDivider(vdouble& v, vdouble& divider);// Наибольший общий делитель двух полиномов
	double PolynomValue(const double& a);// Возвращает значение полинома для заданной точки
	complex PolynomValue(complex& z);// Возвращает значение полинома для заданной точки
	vdouble PolynomValues(vdouble& a);// Возвращает массив значений полинома для заданного массива точек 
	Vector<double> PolynomDerivativesValue(const double& a, int N = 0);// Возвращает значение полинома и его производных порядка до N включительно для заданной точки. Если N = 0, вычисляет производные всех возможных порядков. Обобщенный метод Горнера
	Vector<vdouble> PolynomDerivativesValues(vdouble& a, int N = 0);//Возвращает массивы значений полинома и его производных порядка до N включительно для заданного массива точек. Если N = 0, вычисляет производные всех возможных порядков.  Обобщенный метод Горнера
	vdouble PolynomSubsVariable(const double& a);// Производит замену переменной y = x - a 
//	double MaxAbsRoots();// Максимальный модуль корней полинома
//	double MinAbsRoots();// Минимальный модуль корней полинома
	int roots(vdouble& dr, Vector<complex>& cr, Vector<int>& order_dr, Vector<int>& order_cr);// Вычисляет корни действительного полинома - действительные и комплексные, отдельно - кратные
	int Lobachevski_Greffe_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& epsilon_control = 1.0e-2);//Вычисляет действительные и комплексные корни действительного полинома методом Лобачевского - Греффе (для полиномов с вычленёнными кратными корнями)
	int Bernulli_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& depsilon = 1.0e-8);//Вычисляет действительные и комплексные корни действительного полинома методом Бернулли (для полиномов с вычленёнными кратными корнями)
	int BernulliMinRealRoot(vdouble& dr, const double& depsilon = 1.0e-8);
	int PolynomNewtonRoot(complex& z, const double& epsilon = 1.0e-14);// Уточнение комплексного корня 
	int PolynomNewtonRoot(double& dr, const double& epsilon = 1.0e-16);// Уточнение действительного корня
	int TranscendentNewtonRoot(double& x, double k, vdouble& v, const double& epsilon = 1.0e-16);// Уточнение решения трансцендентного уравнения this->PolynomValue(x) * exp(k * x) + v.PolynomValue(x) = 0.0;
	int PolynomLinaThree_memberDivider(double& p, double& q); // нахождение квадратичного делителя заданного многочлена методом Лина
	int PolynomLinaDivider(vdouble& d); // нахождение делителя любой степени заданного многочлена методом Лина
	double MaxAbsRoots(); // Возвращает максимально возможный модуль корня полинома
	double MinAbsRoots(); // Возвращает минимально возможный модуль корня полинома
	void WriteRaporto(CString& s);
	int WaveletDecomposition_(vdouble& t,
	  int wf, // флаг вейвлета
	  int order, // порядок вейвлета
	  int& maxLevel, // максимальный уровенть разложения
	  Vector<vdouble>& vt,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vs_right, // контейнер для хранения правых хвостовых s- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vd_right, // контейнер для хранения правых хвостовых d- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<vdouble>& vFast); // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
int vdouble::WaveletDecomposition(int wf, // флаг вейвлета
	  int order, // порядок вейвлета
	  int& maxLevel, // максимальный уровенть разложения
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vs); // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
};

struct LagerStruct
{
	double alpha; // alpha - параметр обобщённого полинома Лагерра
	double beta; // beta - параметр обобщённого полинома Лагерра
	double epsilon; // Максимальный модуль детерминанта фундаментальной системы уравнений
	int maxOrder; // Максимально допустимый порядок

	vdouble vQ;// Коэффициенты разложения по Лаггерам
	vdouble alphai; // Промежуточный числитель
	vdouble flip_betai; // Промежуточный знаменатель (обращённый)
	vdouble num;// Числитель передаточной функции
	vdouble den;// Знаменатель передаточной функции
	double error;// Ошибка реконструкции
	double fund_det;// детерминант фундаментальной системы уравнений

};


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//##1
vdouble inline operator+(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr, "Error using operator+ : the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr, "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) + *(pv2+i);
	}
	return tempOb;
}

vdouble inline operator+(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) + a;
	}
	return tempOb;
}

vdouble inline operator+(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) + a;
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//1
vdouble inline operator-(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr, "Error using operator-: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr, "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) - *(pv2+i);
	}
	return tempOb;
}

//3

vdouble inline operator-(const double& a, vdouble& ob2)
{
	int len = ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob2.m_isgorizontal;
	double *pv, *pr; 
	pv = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a - *(pv+i);
	}
	return tempOb;
}

//5

vdouble inline operator-(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) - a;
	}
	return tempOb;
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble inline operator^(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using operator^: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv1+i) , *(pv2+i) );
	}
	return tempOb;
}

//3
vdouble inline operator^(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(a,*(pv+i));
	}
	return tempOb;
}

//5
vdouble inline operator^(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv+i),a);
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble inline pow(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using pow(): the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv1+i) , *(pv2+i) );
	}
	return tempOb;
}
//3
vdouble inline pow(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(a,*(pv+i));
	}
	return tempOb;
}
//5
vdouble inline pow(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv+i),a);
	}
	return tempOb;
}
///////////////////////////////
//1
vdouble inline operator*(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using operator*: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) * *(pv2+i) ;
	}
	return tempOb;
}

//3
vdouble inline operator*(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a * *(pv+i);
	}
	return tempOb;
}
//4
vdouble inline operator*(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) =  *(pv+i) * a ;
	}
	return tempOb;
}
///////////////////////////////
///////////////////////////////
//1
vdouble inline operator/(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using operator/: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) / *(pv2+i) ;
	}
	return tempOb;
}
//3
vdouble inline operator/(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a / *(pv+i);
	}
	return tempOb;
}
//5
vdouble inline operator/(vdouble& ob, const double& a)
{
//	ob.WriteRaporto((CString)" operator/(vdouble& ob, const double& a) \t");
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) / a;
	}
//ob.WriteRaporto((CString)" operator/ End \n");
	return tempOb;
}
///////////////////////////////
///////////////////////////////
//1
vdouble inline operator,(vdouble& ob1, vdouble& ob2)
{
	int i;
	int len1 = ob1.m_length;
	int len = len1 + ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(i=0;i<len1;i++)
	{
		*(pr+i) = *(pv1+i);
	}
	for(i=len1; i<len; i++)
	{
		*(pr+i) = *(pv2+i);
	}
	return tempOb;
}
//3
vdouble inline operator,(const double& a, vdouble& ob)
{
	int len = ob.m_length + 1;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	*pr = a;
	for(int i=1;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	return tempOb;
}
//5
vdouble inline operator,(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb=vdouble(len+1);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	*(pr+len) = a;
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline operator+(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = +(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline operator-(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = -(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
vdouble inline log(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = log(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline log10(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = log10(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline abs(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = fabs(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline acos(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = acos(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline asin(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = asin(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline atan(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = atan(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////

vdouble inline atan2(vdouble& x, vdouble& y)
{
	int len = x.m_length;
	if (len != y.m_length)
	{
		fprintf(stderr,  "Error using atan2: the lengthes of the vectors must be the same\n");
		return vdouble(0);

	}
	if (x.m_isgorizontal != y.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=x.m_isgorizontal;
	double *px, *py, *pr; 
	px = x.pD;
	py = y.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = atan2(*(px+i) , *(py+i));
	}
	return tempOb;
}

//////////////////////////////////////////////////////////////
vdouble inline cos(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = cos(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline cosh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = cosh(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sin(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sin(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sinh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sinh(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline tan(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = tan(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline tanh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = tanh(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sqrt(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sqrt(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
vdouble inline exp(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = ::exp(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline floor(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = floor(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline ceil(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = ceil(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator>(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) > (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator>(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a > (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) > a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator>=(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) >= (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator>=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a >= (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) >= a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator<(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) < (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator<(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a < (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator<(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) < a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator<=(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) <= (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator<=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a <= (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator<=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) <= a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator==(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) == (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator==(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a == (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator==(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) == a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator!=(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) != (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator!=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a != (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator!=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) != a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
vdouble inline fliplr(vdouble& ob)
{
	vdouble v;
	int len = ob.m_length;
	v.resize(len);
	double *pv, *pob;
	pv = v.pD;
	pob = ob.pD + len - 1;
	for (int i = 0; i < len; i++)
	{
		*(pv + i) = *pob;
		pob--;
	}
	return v;
}
//////////////////////////////////////////////////////////////
void inline operator<<(vdouble& ob, const double& a)
{
	int len_1 = ob.m_length - 1;
	if ( len_1 < 0)
		return;
	double *pv, *pr; 
	pv = ob.pD + 1;
	pr = ob.pD;
	for (int i = 0; i < len_1; i++)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr + len_1) = a;
}
void inline operator>>(const double& a, vdouble& ob)
{
	int len_1 = ob.m_length - 1;
	if ( len_1 < 0)
		return;
	double *pv, *pr; 
	pv = ob.pD - 1;
	pr = ob.pD;
	for (int i = len_1; i > 0; i--)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr) = a;
}
vdouble inline conv(vdouble& v1, vdouble& v2)
{
	int len, len1, len2, i, j, milen, malen;
	double *pc, *pci, *pmai, *pmi, *pma;
	len1 = v1.m_length;
	len2 = v2.m_length;

	len = len1 + len2 - 1;
	if (len < 0)
		len = 0;

	vdouble c = vdouble(len); pc = c.pD;

	bool bl = len1 <= len2;

	pmi = bl ? v1.pD : v2.pD;
	pma = bl ? v2.pD : v1.pD;
	milen = bl ? len1 : len2;
	malen = bl ? len2 : len1;

	for (i = 0; i < milen; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = 0; j <= i; j++)
			*pci += *(pmi + j) * *(pmai - j);
	}
	for (i = milen; i < malen; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = 0; j < milen; j++)
			*pci += *(pmi + j) * *(pmai - j);
	}
	for (i = malen; i < len; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = i - malen +1; j < milen; j++) 
			*pci += *(pmi + j) * *(pmai - j);
	}
	return c;
	
}
void inline operator<<(CArchive& ar, vdouble& v)
{
	ar << v.m_length;
	ar << v.m_dims;
	for (int dim = 0; dim < v.m_dims; dim++)
		ar << v.m_size[dim];

	double *vpD;
	vpD = v.pD;

	for (int i = 0; i < v.m_length; i++)
		ar << *(vpD + i);

}
void inline operator>>(CArchive& ar, vdouble& v)
{
	ar >> v.m_length;
	ar >> v.m_dims;
	v.m_size = Vector<int>(v.m_dims);
	for (int dim = 0; dim < v.m_dims; dim++)
		ar >> v.m_size[dim];

	vdouble::m_nConstructions++;

	if ((v.pD = (double*)malloc(v.m_length*SD)) == NULL && v.m_length != 0)
	{
		v.m_length = 0;
		AfxMessageBox("operator>>(CArchive& ar, vdouble& v) - Not enough memory");
		AfxThrowMemoryException();
		return;
	};
	vdouble::m_szMemory +=v.m_length*SD;
	v.m_isgorizontal=true;

	double *vpD;
	vpD = v.pD;

	for (int i = 0; i < v.m_length; i++)
		ar >> *(vpD + i);

}

//##2
#endif
