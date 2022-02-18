// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
#define AFX_GRAPH_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct TData
{
	//===== Порядок в нормализованном представлении числа
	int Power;
	//===== Флаг оси X
	bool bX;
	double
		//======= Экстремумы
		Min, Max,
		//======= Множитель (10 в степени Power)
		Factor,
		//======= Шаг вдоль оси (мантисса)
		Step,
		//======= Реальный шаг
		dStep,
		//======= Первая и последняя координаты (мантиссы)
		Start, End,
		//======= Первая и последняя координаты
		dStart, dEnd;
};

	//===== Класс, реализующий функции плоского графика
class CGraph
{
public:
//	CSize m_SizeTotal;
//	int m_yshift;
	//===== Данные, характеризующие данные вдоль осей
	TData m_DataX, m_DataY;
	//===== Контейнеры точек графика
	Vector<CpVDPoints> & m_vpPoints;
	//===== Текущие размеры окна графика
	CSize m_Size;
	//===== Экранные координаты центра окна
	CPoint m_Center;
	//===== Заголовок и наименования осей
	CString m_sTitle, m_sX, m_sY;
	//===== Перо для рисования
	CPen m_Pen;
	//===== Два типа шрифтов
	CFont m_TitleFont, m_Font;
	CFont m_PrintTitleFont, m_PrintFont;
	//===== Высота буквы (зависит от шрифта)
	int		m_LH;
	//===== Толщина пера
	Vector<int>	m_vWidth;
	//===== Цвет пера
	Vector<COLORREF> m_vClr;
	//======= Методы для управления графиком
//	CGraph(){}
	CGraph(Vector<CpVDPoints> & pt, CString sTitle,
					CString sX, CString sY);
	virtual ~CGraph();
	//===== Заполнение TData для любой из осей
	void Scale(TData& data);
	//===== Переход к логическим координатам точек
	int MapToLogX (double d);
	int MapToLogY (double d);
	int MapToLogYPrint (double d);
	//===== Изображение в заданном контексте
	void Draw (CDC *pDC, TData& DataX, TData& DataY, bool toScaleX = false, bool toScaleY = false);
	//===== Изображение одной линии
	void DrawLine(CDC *pDC, bool isPrint);
	//===== Подготовка цифровой метки на оси
	CString MakeLabel(bool bX, double& d);
};

#endif // !defined(AFX_GRAPH_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
