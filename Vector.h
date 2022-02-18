//#include "stdafx.h"

#if !defined(_VECTOR333_)
#define _VECTOR333_

template <class T> class Vector
{
	friend class vdouble;
//====== Данные класса 
private:
	int size;		// Размер массива
//	bool m_Constructed;
//====== Методы класса
public:
	T *data;		// Указатель начала массива компонент
	Vector();
	Vector(int);
	Vector(const Vector<T>& v);
	~Vector() 
	{
		size = 0;
		free(data); 
		/* cout<< "Vector<T> destructor"<<endl;*/
	}
	int Size() { return size; }  // Возвращает длину вектора
	T Max() // Возвращает мaксимальный элемент вектора
	{
		T _Max;
		_Max=*(data);
		for(int i=1;i<size;i++)
			_Max = _Max > *(data+i) ? _Max : *(data+i);
		return _Max;
	}
	T Min() // Возвращает минимальный элемент вектора
	{
		T _Min;
		_Min=*(data);
		for(int i=1;i<size;i++)
			_Min = _Min < *(data+i) ? _Min : *(data+i);
		return _Min;
	}

	T& operator [](int i) 
	{ 
		if (i < 0 || i >= size)
		{
			CString strerr;
			strerr.Format("Index = %i Error using Vector<size = %i>::Operator[]", i, size);
			AfxMessageBox(strerr);
			return data[i];
		}
		return data[i]; 
	}

	void resize(unsigned int _size)
	{
		if (size > 0)
			free(data);
		size = (int)_size;
		if ((data = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
		{
			AfxMessageBox("Vector<T>::push_back(const T& a) - Not enough memory");
			return;
		}
	}
	void resize(unsigned int _size, const T a)
	{
		if (size > 0)
			free(data);
		size = (int)_size;
		if ((data = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
		{
			AfxMessageBox("Vector<T>::push_back(const T& a) - Not enough memory");
			return;
		}
		for(int i=0; i<size; i++)
			*(data+i) = a;
	}
	void clear()
	{
		free(data); 
		size = 0;
		/* cout<< "Vector<T> destructor"<<endl;*/
	}
	bool empty()
	{
		return size == 0 ? true : false;
	}
	void push_back(const T& a) // Добавляет элемент в конец вектора
	{
		int size_1 = size;
		size++; 
		T *data2;
		if ((data2 = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
		{
			AfxMessageBox("Vector<T>::push_back(const T& a) - Not enough memory");
			return;
		};
		for(int i=0; i<size_1; i++)
			*(data2+i) = *(data+i);
		*(data2+size_1) = a;
		if (data != 0) free(data);
		data=data2;
	}
	void push_back(T& a) // Добавляет элемент в конец вектора
	{
		int size_1 = size;
		size++; 
		T *data2;
		if ((data2 = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
		{
			AfxMessageBox("Vector<T>::push_back(T& a) - Not enough memory");
			return;
		};
		for(int i=0; i<size_1; i++)
			*(data2+i) = *(data+i);
		*(data2+size_1) = a;
		if (data != 0) free(data);
		data=data2;
	}
	void DeleteAll() // Удаляет все элементы вектора
	{
		if (size != 0)
		{
			size = 0;
			T *data2;
			data2 = (T*)malloc(size*sizeof(T));
			if (data != 0) free(data);
			data=data2;
		}
	}
	void DeleteElement(const int& index) // Удаляет index-ный элемент вектора
	{
		if (index > size-1 || index < 0)
		{
			cout<< "Error using Vector::DeleteElement(int index) : index out of Vector's indexes \n";
			return;
		}
		size--;
		T *data2;
		if ((data2 = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
		{
			AfxMessageBox("Vector<T>::DeleteElement(int index) - Not enough memory");
			return;
		};
		for(int i=0; i<index; i++)
			*(data2+i) = *(data+i);
		for(i=index; i<size; i++)
			*(data2+i) = *(data+i+1);
		if (data != 0) free(data);
		data=data2;
	}
	void DeleteElements(Vector<bool>& vbl) // Удаляет элементы вектора
	{
		if (size != vbl.Size())
		{
			AfxMessageBox("Error using Vector::DeleteElements(Vector<bool>& vbl) : size of input bool vector must be equial to size of current Vector\n");
			return;
		}
		int old_size = size;
		int j=-1;// new indexes
		size -= Find(vbl).Size();
		T *data2;
		if ((data2 = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
		{
			AfxMessageBox("Vector::DeleteElements(Vector<bool>& vbl) - Not enough memory");
			return;
		};

		for(int i=0; i<old_size; i++) //  old indexes
		{
			if (! vbl[i])
			{
				j++;
				*(data2+j) = *(data+i);
			}
		}
		if (data != 0) free(data);
		data=data2;
	}
	T& End() // Возвращает последний элемент вектора
	{
		return data[size - 1];
	}
	T Product()
	{
		if (size < 1)
		{
			AfxMessageBox("T Product()(size < 1)");
			return (T)0;
		}
		T prod;
		prod = data[0];
		for(int i=1; i<size; i++)
			prod *= data[i];
		return prod;
	}
	T Product(int i1, int i2)
	{
		if (size < 1)
		{
			AfxMessageBox("T Product()(size < 1)");
			return (T)0;
		}
		if (i1 < 0)
		{
			AfxMessageBox("T Product()(i1 < 0)");
			return (T)0;
		}
		if (i2 < 0)
		{
			AfxMessageBox("T Product()(i2 < 0)");
			return (T)0;
		}
		if (i1 >= size)
		{
			AfxMessageBox("T Product()(i1 >= size)");
			return (T)0;
		}
		if (i2 >= size)
		{
			AfxMessageBox("T Product()(i2 >= size)");
			return (T)0;
		}
		T prod;
		prod = data[i1];
		for(int i=i1; i<i2; i++)
			prod *= data[i];
		return prod;
	}
/*	void disp()
	{
		AfxMessageBox("Function disp is unworked");
		for(int i=0;i<size;i++)
		{
			cout << "   ";
			cout << *(data+i);
		}
		cout << endl << endl;
		
	}*/
	Vector<T>& operator=(Vector<T>& v)
	{
		if (this == &v)
			return *this;
		if  (size != v.size)
		{
			if (size >= 1) 	free(data);
			size=v.size;
			if ((data = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
			{
				AfxMessageBox("Vector<T>::Vector(int n) - Not enough memory");
				return *this;
			};
		}
		T *vdata;
		vdata = v.data;
		for(int i=0; i< size; i++)
		{
			*(data+i) = *(vdata+i);
		}
		return *this;
	}

	friend Vector<int> inline Find(Vector<bool>& vbl);
	friend Vector<bool> inline operator!(Vector<bool>& vb);

	friend Vector<bool> inline operator||(Vector<bool>& vb, bool& bl);
	friend Vector<bool> inline operator||(bool& bl, Vector<bool>& vb);
	friend Vector<bool> inline operator||(Vector<bool>& vb1, Vector<bool>& vb2);

	friend Vector<bool> inline operator&&(Vector<bool>& vb, bool& bl);
	friend Vector<bool> inline operator&&(bool& bl, Vector<bool>& vb);
	friend Vector<bool> inline operator&&(Vector<bool>& vb1, Vector<bool>& vb2);
	//=================== Логические операторы =============================
	//////////////////////////////////////////////////////////////
	friend Vector<bool> inline operator>(Vector<int>& ob1, Vector<int>& ob2);
	friend Vector<bool> inline operator>(const int& a, Vector<int>& ob);
	friend Vector<bool> inline operator>(Vector<int>& ob, const int& a);

};
//====== Внешняя реализация тела конструктора
template <class T> Vector<T>::Vector()
{
	int zero = 0;
	data = (T*)malloc(zero);
	size=zero;
}
template <class T> Vector<T>::Vector(int n)
{
	size=n;
	if ((data = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
	{
		AfxMessageBox("Vector<T>::Vector(int n) - Not enough memory");
		return;
	}
}
template <class T> Vector<T>::Vector(const Vector<T>& v)
{
	size=v.size;
	if ((data = (T*)malloc(size*sizeof(T))) == NULL && size != 0)
	{
		AfxMessageBox("Vector<T>::Vector(int n) - Not enough memory");
		return;
	};
	T *vdata;
	vdata = v.data;
	for(int i=0; i< size; i++)
	{
		*(data+i) = *(vdata+i);
	}
	return;
}

Vector<int> inline Find(Vector<bool>& vbl)
{
	int sz = vbl.size;
	int len = 0;
	int i;
	for (i = 0; i < sz; i++)
	{
		if (vbl[i])
			len++;
	}
	Vector<int> indexes(len);
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		if (vbl[i])
		{
			indexes[j] = i;
			j++;
		}
	}
	return indexes;
}

//////////////////////////////////////////////////////////////
Vector<bool> inline operator!(Vector<bool>& vb)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = vb.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr+i) = !(*(pv+i));
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
Vector<bool> inline operator||(Vector<bool>& vb, bool& bl)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = vb.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv + i) || bl ;
	}
	return vbl;
}

Vector<bool> inline operator||(bool& bl, Vector<bool>& vb)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = vb.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = bl || *(pv + i);
	}
	return vbl;
}

Vector<bool> inline operator||(Vector<bool>& vb1, Vector<bool>& vb2)
{
	int sz = vb1.size;
	if (sz != vb2.size)
	{
		fprintf(stderr,"Error using Vector<bool> inline operator||(Vector<bool>& vb1, Vector<bool>& vb2):\n");
		fprintf(stderr,"Lengthes of compared bool vectors = %i, %i must be equial",
			vb1.size, vb2.size);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(sz);
	bool *pv1, *pv2, *pr;
	pv1 = vb1.data;
	pv2 = vb2.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv1 + i) || *(pv2 + i);
	}
	return vbl;
}

//////////////////////////////////////////////////////////////
Vector<bool> inline operator&&(Vector<bool>& vb, bool& bl)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = vb.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv + i) && bl ;
	}
	return vbl;
}

Vector<bool> inline operator&&(bool& bl, Vector<bool>& vb)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = vb.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = bl && *(pv + i);
	}
	return vbl;
}

Vector<bool> inline operator&&(Vector<bool>& vb1, Vector<bool>& vb2)
{
	int sz = vb1.size;
	if (sz != vb2.size)
	{
		fprintf(stderr,"Error using Vector<bool> inline operator&&(Vector<bool>& vb1, Vector<bool>& vb2):\n");
		fprintf(stderr,"Lengthes of compared bool vectors = %i, %i must be equial",
			vb1.size, vb2.size);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(sz);
	bool *pv1, *pv2, *pr;
	pv1 = vb1.data;
	pv2 = vb2.data;
	pr = vbl.data;
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv1 + i) && *(pv2 + i);
	}
	return vbl;
}
//=================== Логические операторы =============================
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>(Vector<int>& ob1, Vector<int>& ob2)
{
	int len = ob1.size;
	if (len != ob2.size)
	{
		fprintf(stderr,"Error using Vector<T> operator>(Vector<T> ob1, Vector<T>& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.size, ob2.size);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	int *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.data;
	pv2 = ob2.data;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) > (*(pv2+i));
	}
	return vbl;
}

Vector<bool> inline operator>(const int& a, Vector<int>& ob)
{
	int len = ob.size;
	Vector<bool> vbl(len);
	int *pv; 
	bool *pr;
	pv = ob.data;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a > (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>(Vector<int>& ob, const int& a)
{
	int len = ob.size;
	Vector<bool> vbl(len);
	int *pv; 
	bool *pr;
	pv = ob.data;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) > a;
	}
	return vbl;
}


#endif