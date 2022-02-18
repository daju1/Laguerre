// DPoint.h: interface for the CDPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_)
#define AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <AFXWIN.H>
//====== Новый класс "Вещественная точка"
/*
class CDPoint
{
public:
	double x;
	double y;		//===== Вещественные координаты

	//====== Конструктор по умолчанию
	CDPoint();
	~CDPoint();

	//====== Конструктор копирования
	CDPoint(const CDPoint& pt)
	{
		x = pt.x;
		y = pt.y; 
	}

	//====== Конструктор с параметрами
	CDPoint(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
	
	//====== Операция умножения (увеличение в n раз)
	CDPoint operator*(int n)
	{
		return CDPoint (x*n,  y*n); 
	}

	//====== Операция присваивания
	CDPoint& operator=(const CDPoint& pt) 
	{
		x = pt.x;	
		y = pt.y;
		return *this;		// Возвращаем свой адрес
	}
	
	//====== Операция сложения двух точек
	CDPoint operator+(CDPoint& pt) 
	{
		return CDPoint(x + pt.x, y + pt.y);
	}
	
	//====== Операция вычитания двух точек
	CDPoint operator-(CDPoint& pt) 
	{
		return CDPoint(x - pt.x, y - pt.y);
	};
	
	// Метод для преобразования к типу CPoint (целая точка)
	CPoint ToInt() 
	{
		return CPoint(int(x),int(y));
	}
	
	//====== Операция сложения с записью результата
	void operator+=(CDPoint& pt) { x += pt.x;		y += pt.y; }
	
	//====== Операция вычитания с записью результата
	void operator-=(CDPoint& pt) { x -= pt.x;		y -= pt.y; }

	//====== Операция вычисления нормы вектора, заданного точкой
	double operator! () { return fabs(x) + fabs(y); }
};


typedef Vector<CDPoint> VECPTS;
*/

struct CpVDPoints
{
	bool toDraw; // надо ли рисовать
	vdouble* px; // указатель на вектор x 
	vdouble* py; // указатель на вектор y 
};

#endif // !defined(AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_)
