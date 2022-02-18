// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphs.h"
//#include "GraphsView.h"
#include "Graph.h"

//===== Доля окна, занимаемая графиком
#define SCALE_X 0.75
#define SCALE_Y 0.75
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//======= Конструктор класса CGraph
CGraph::CGraph (Vector<CpVDPoints>& pt, 
				CString sTitle,
				CString sX, CString sY): m_vpPoints(pt)
{
	int n;
//	m_SizeTotal = sizeTotal;
//	m_yshift = yshift;
	// Число графиков
	//======= Готовим данные, характеризующие оси координат	ZeroMemory(&m_DataX, sizeof(TData));
	ZeroMemory(&m_DataY, sizeof(TData));
	m_DataX.bX = true;
	m_DataY.bX = false;
	m_sTitle = sTitle;
	m_sX = sX;
	m_sY = sY;

	//======= Создаем шрифт для оцифровки осей
	m_Font.CreateFont(12,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= Создаем шрифт для оцифровки осей
	m_PrintFont.CreateFont(36,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= Выясняем вертикальный размер буквы
	TEXTMETRIC tm;
	CClientDC dc(0);
	dc.SelectObject(&m_Font);
	dc.GetTextMetrics(&tm); 
	m_LH = tm.tmHeight;

	//======= Создаем шрифт для вывода заголовка
	m_TitleFont.CreateFont(16,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	//======= Создаем шрифт для вывода заголовка
	m_PrintTitleFont.CreateFont(150,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	int nGraphs = 10;
	m_vClr.resize(nGraphs);
	//======= Задаем параметры пера
	for (n = 0; n < nGraphs; n++)
	{
		switch(n)
		{
		case 0:	m_vClr[n] = RGB(100,100,0);break;//Open
		case 1:	m_vClr[n] = RGB(255,0,0);break;//High
		case 2:	m_vClr[n] = RGB(0,0,255);break;//Low
		case 3:	m_vClr[n] = RGB(0,255,0);break;//Close
		case 4:	m_vClr[n] = RGB(255,0,0);break;
		case 5:	m_vClr[n] = RGB(255,0,0);break;
		case 6:	m_vClr[n] = RGB(100,100,0);break;
		case 7:	m_vClr[n] = RGB(100,100,0);break;
		case 8:	m_vClr[n] = RGB(0,0,0);break;
		case 9:	m_vClr[n] = RGB(0,0,0);break;
		default:m_vClr[n] = RGB(0,0,0);break;
		}
	}
	m_vWidth.resize(nGraphs);
	for ( n = 0; n < nGraphs; n++)
	{
		switch(n)
		{
		case 0:	m_vWidth[n] = 1;break;
		case 1:	m_vWidth[n] = 1;break;
		case 2:	m_vWidth[n] = 1;break;
		case 3:	m_vWidth[n] = 1;break;
		case 4:	m_vWidth[n] = 1;break;
		case 5:	m_vWidth[n] = 1;break;
		case 6:	m_vWidth[n] = 1;break;
		case 7:	m_vWidth[n] = 1;break;
		case 8:	m_vWidth[n] = 1;break;
		case 9:	m_vWidth[n] = 1;break;
		default:m_vWidth[n] = 1;break;
		}
	}
}

//======= Деструктор 
CGraph::~CGraph(){}

//===== Внешняя функция нормировки мантисс шагов сетки
void gScale (double span, double& step)
{
	//===== Переменная span определяет диапазон изменения
	//===== значаний одной из координат точек графика
	//===== Вычисляем порядок числа, описывающего диапазон
	int power = int(floor(log10(span)));
	//===== Множитель (zoom factor)
	double factor = pow(10.0, power);
	//===== Мантисса диапазона (теперь 1 < span < 10)
	span /= factor;

	//===== Выбираем стандартный шаг сетки
	if (span<1.99)
		step=.2;
	else if (span<2.49)
		step=.25;
	else if (span<4.99)
		step=.5;
	else if (span<10.)
		step= 1.;

	//===== Возвращаем реальный шаг сетки (step*10^power)
	step *= factor; 
}

void CGraph::Scale (TData& data)
{
	//===== С пустой последовательностью не работаем
//	if (m_vPoints.empty())
//		return;
		//===== Готовимся искать экстремумы
	
	double Max,
		Min;
	int i = 0;
	bool findfirst = true;
	do
	{
		if (m_vpPoints[i].toDraw && m_vpPoints[i].px->Length() > 0 && m_vpPoints[i].py->Length() > 0)
		{
			data.Max = data.bX ? m_vpPoints[i].px->Max() : m_vpPoints[i].py->Max();
			data.Min = data.bX ? m_vpPoints[i].px->Min() : m_vpPoints[i].py->Min();
			findfirst = false;
		}
		i++;
	}
	while (i < m_vpPoints.Size() && findfirst);

	for(int n = i; n < m_vpPoints.Size(); n++)
	{
		if (m_vpPoints[n].toDraw && m_vpPoints[n].px->Length() > 0 && m_vpPoints[n].py->Length() > 0)
		{
			Max = data.bX ? m_vpPoints[n].px->Max() : m_vpPoints[n].py->Max();
			Min = data.bX ? m_vpPoints[n].px->Min() : m_vpPoints[n].py->Min();
			data.Max = data.Max > Max ? data.Max : Max;
			data.Min = data.Min < Min ? data.Min : Min;
		}
	}

	//====== Выводим экстремумы функции	

	//===== Максимальная амплитуда двух экстремумов 
	double ext = max(fabs(data.Min),fabs(data.Max));

	//===== Искусственно увеличиваем порядок экстремума
	//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
	//===== не переходя к экспоненцеальной форме чисел 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	data.Power = int(floor(power/7.));

	//===== Если число не укладывается в этот диапазон
	if (data.Power != 0)
		//===== то мы восстанавливаем значение порядка
		data.Power = int(floor(power)) - 3;
	//===== Реальный множитель
	data.Factor = pow(10.0, data.Power);

	//===== Диапазон изменения мантиссы
	double span = (data.Max - data.Min)/data.Factor;
	//===== Если он нулевой,
	if (span == 0.)
		span = 0.5; // то искусственно раздвигаем график

	//===== Подбираем стандартный шаг для координатной сетки
	gScale (span, data.Step);

	//===== Шаг с учетом искусственных преобразований
	data.dStep = data.Step * data.Factor;

	//===== Начальная линия сетки должна быть кратна шагу
	//===== и быть меньше минимума
	data.dStart = data.dStep * int(floor(data.Min/data.dStep));
	data.Start = data.dStart/data.Factor;

	//===== Вычисляем последнюю линию сетки
	for (data.End = data.Start;
		data.End < data.Min/data.Factor + span-1e-10;  
		data.End += data.Step)
		;
	data.dEnd = data.End*data.Factor;
}

int CGraph::MapToLogX (double d)
{
	return m_Center.x + int (SCALE_X * m_Size.cx * d);
}

int CGraph::MapToLogY (double d)
{
	return m_Center.y - int (SCALE_Y * m_Size.cy * d);
}
int CGraph::MapToLogYPrint (double d)
{
	return m_Center.y - int (SCALE_Y * m_Size.cy * d);
}

void CGraph::Draw (CDC *pDC, TData& DataX, TData& DataY, bool toScaleX, bool toScaleY)
{
	for (int n = 0; n < m_vpPoints.Size(); n++)
	{
		if (m_vpPoints [n].toDraw)
		{
			if (m_vpPoints [n].px -> m_length != m_vpPoints [n].py -> m_length)
			{
				CString errstr;
				errstr.Format(" Number of line = %i\n px -> m_length (%i) != py -> m_length (%i)\n",
					n, m_vpPoints [n].px -> m_length, m_vpPoints [n].py -> m_length);
				AfxMessageBox("Error using CGraph::Draw()\n" + errstr);
				return;
				// AfxThrowUserException();
			}
		}
	}
	//====== С помощью контекста устройства
	//====== узнаем адрес окна, его использующего
	CRect r;
	
	bool isPrint = pDC->IsPrinting() != 0;
	if(!isPrint)
	{
		CWnd *pWnd = pDC->GetWindow();
		pWnd->GetClientRect(&r);
//		((CGraphsView*)pWnd)->GetTotalSize(m_SizeTotal);
	}
	else
	{
		r.left = 20;
		r.top = 20;
		r.right = r.left + pDC->GetDeviceCaps(HORZRES);
		r.bottom = r.top + pDC->GetDeviceCaps(VERTRES);
	}

	//====== Уточняем размеры окна
	m_Size = r.Size();
	if(!isPrint)
	{
		m_Center = CPoint(m_Size.cx/2, m_Size.cy/2);
	}
	else
	{
		m_Center = CPoint(m_Size.cx/2, m_Size.cy/2);
	}
	/*
	FILE *st;
	st = fopen("D:\\out.txt", "at");

	fprintf(st,"x =%i , y = %i", m_Size.cx, m_Size.cy);
	fclose(st);*/
	int nDC = pDC->SaveDC();
	
	//====== Создаем черное перо для изображения рамки
	CPen pen(PS_SOLID, 0, COLORREF(0));
	pDC->SelectObject(&pen);

	//====== Преобразуем координаты рамки
	int lt = MapToLogX(-0.5),
		rt = MapToLogX(0.5),
		tp = isPrint ? MapToLogYPrint(0.5) : MapToLogY(0.5),
		bm = isPrint ? MapToLogYPrint(-0.5) : MapToLogY(-0.5);

	pDC->Rectangle (lt, tp, rt, bm);

	//====== Задаем цвет и выравнивание текста
	pDC->SetTextColor(0);
	pDC->SetTextAlign(TA_LEFT | TA_BASELINE);
	
	//====== Выбираем шрифт
	if(!isPrint)
		pDC->SelectObject (&m_Font);
	else
		pDC->SelectObject (&m_PrintFont);

	if (toScaleX)
	{
		// Атрибуты координатных осей используем готовые с предыдущего графика
		m_DataX = DataX;
	}
	else
	{
		//====== Вычисляем атрибуты координатных осей
		Scale(m_DataX);
		DataX = m_DataX;
	}
	if (toScaleY)
	{
		// Атрибуты координатных осей используем готовые с предыдущего графика
		m_DataY = DataY;
	}
	else
	{
		//====== Вычисляем атрибуты координатных осей
		Scale(m_DataY);
		DataY = m_DataY;
	}

	//====== Выводим экстремумы функции	
	CString s;
	s.Format("Min = %.3g",m_DataY.Min);
	pDC->TextOut(rt+m_LH, tp+m_LH, s);

	s.Format("Max = %.3g",m_DataY.Max);
	pDC->TextOut(rt+m_LH, tp+m_LH+m_LH, s);
		
	//====== Готовимся изображать координатную сетку
	CPen gridPen(PS_SOLID, 0, RGB(92,200,178));
	pDC->SelectObject(&gridPen);
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	
	//====== Рисуем вертикальные линии сетки
	for (double x = m_DataX.Start;  
			x < m_DataX.End - m_DataX.Step/2.;
			x += m_DataX.Step)
	{
		//====== Нормируем координату x
		double	xn = (x - m_DataX.Start) /
						(m_DataX.End - m_DataX.Start) - 0.5;

		//====== Вычисляем оконную координату
		int xi = MapToLogX(xn);	
		//====== Пропускаем крайние линии,
		//====== так как они совпатают с рамкой
		if (x > m_DataX.Start && x < m_DataX.End)
		{
			pDC->MoveTo(xi, bm);
			pDC->LineTo(xi, tp);
		}
		//====== Наносим цифровую метку
		pDC->TextOut(xi, bm+m_LH, MakeLabel(true, x));
	}

	//===== Повторяем цикл для горизонтальных линий сетки
	pDC->SetTextAlign(TA_RIGHT | TA_BASELINE);
	for (double y = m_DataY.Start;
			y < m_DataY.End - m_DataY.Step/2.;
			y += m_DataY.Step)
	{
		double yn = (y - m_DataY.Start) /
						(m_DataY.End - m_DataY.Start) - 0.5;

		int yi = isPrint ? MapToLogYPrint(yn) : MapToLogY(yn) ;
		if (y > m_DataY.Start && y < m_DataY.End)
		{
			pDC->MoveTo(lt, yi);
			pDC->LineTo(rt, yi);
			pDC->TextOut(lt-m_LH/2, yi, MakeLabel(false, y));
		}
	}

	//====== Вывод меток осей
	pDC->TextOut(lt-m_LH/2, tp - m_LH, m_sY);
	pDC->SetTextAlign(TA_LEFT | TA_BASELINE);
	pDC->TextOut(rt-m_LH, bm + m_LH, m_sX);

	//====== Вывод заголовка
	if (m_sTitle.GetLength() > 40)
		m_sTitle.Left(40);


	//====== Выбираем шрифт
	if(!isPrint)
		pDC->SelectObject(&m_TitleFont);
	else
		pDC->SelectObject(&m_PrintTitleFont);
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->TextOut((lt+rt)/2, tp - m_LH, m_sTitle);
	
	//====== Вывод линии графика
	DrawLine(pDC, isPrint);
	//====== Восстанавливаем инструменты GDI
	pDC->RestoreDC(nDC);
}



void CGraph::DrawLine(CDC *pDC, bool isPrint)
{
	for(int n = 0; n <  m_vpPoints.Size(); n++)
	{
		if (m_vpPoints[n].toDraw)
		{
			//====== Уничтожаем старое перо
			if (m_Pen.m_hObject)
				m_Pen.DeleteObject();
			//====== Создаем новое
			m_Pen.CreatePen(PS_SOLID, m_vWidth[n], m_vClr[n]);

			pDC->SelectObject(&m_Pen);

			double	x0 = m_DataX.dStart,
					y0 = m_DataY.dStart,
					dx = m_DataX.dEnd - x0,
					dy = m_DataY.dEnd - y0;

			for (int i=0;  i < m_vpPoints[n].px->Length();  i++)
			{
				//====== Нормируем координаты
				double	x = (m_vpPoints[n].px->operator[](i) - x0) / dx - .5,
						y = (m_vpPoints[n].py->operator[](i) - y0) / dy - .5;

				//====== Переход к оконным координатам
				CPoint pt (MapToLogX(x),isPrint ? MapToLogYPrint(y) : MapToLogY(y));
				//====== Если точка первая, то ставим перо
				if (i==0)
					pDC->MoveTo(pt);
				else
					pDC->LineTo(pt);
			}
		}
	}
}



CString CGraph::MakeLabel(bool bX, double& v)
{
	CString s = "0.0";
	if (v == 0.)
		return s;

	//====== Сначала делаем грубую прикидку
	//====== Пробуем поместиться в 20 позиций
	s.Format("%20.10f",v);
	//====== Выясняем порядок шага сетки,
	//====== переворачивая его знак (трюк)
	int nDigits = int(ceil(-log10(bX ? m_DataX.Step
									: m_DataY.Step)));
	//====== Если все изменения происходят до запятой,
	//====== то цифры после запятой нас не интересуют
	if (nDigits <= 0)
		nDigits = -1;
	else
		if (bX)
			nDigits++;	// Эстетическая добавка

	//====== Слева усекаем все
	s.TrimLeft();

	//====== Справа оставляем минимум разрядов
	s = s.Left(s.Find(".") + nDigits + 1);

	int iPower = bX ? m_DataX.Power : m_DataY.Power;
	//====== Нужен ли порядок?
	if (iPower != 0)
	{
		//====== Нужен, если не поместились в (10^-3, 10^+4)
		CString add;
		add.Format("·e%+d",iPower);
		s += add;
	}
	return s;
}
