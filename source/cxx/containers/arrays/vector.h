/*
Templated Vector

Automatically resizing sequential container

Advantages smallest overhead over other containers

Best suited for a stack.
*/

#ifndef VECTOR
#define VECTOR

template<class T>
class Vector
{
public:
	Vector();
	Vector(int Count);
	~Vector();

	void PushBack(T Value);
	T PopBack();

	inline void Swap(int Index1, int Index2);

	inline void SetValue(int Index, T Value);

	inline T GetAt(int Index);
	inline T operator[](int Index);

	int Size();
	int Capacity();
private:
	bool GrowBy(int Count);
	bool Grow();

	T *m_Data;
	int m_Count;
	int m_End;
};

template<class T>
Vector<T>::Vector()
{
	m_Data = NULL;
	m_Count = 0;
	m_End = 0;
}

template<class T>
Vector<T>::Vector(int Count)
{
	m_Data = NULL;
	m_Count = 0;
	m_End = 0;
	GrowBy(Count);
}

template<class T>
Vector<T>::~Vector()
{
	if(m_Data != NULL)
	{
		delete[] m_Data;
	}
}

template<class T>
void Vector<T>::PushBack(T Value)
{
	if(m_End == m_Count)
	{
		bool result = Grow();
	}
	if(m_End < m_Count)
	{
		m_Data[m_End] = Value;
		m_End++;
	}
}

template<class T>
T Vector<T>::PopBack()
{
	T Value;
	if(m_End > 0)
	{
		Value = m_Data[m_End];
		m_End--;
	}
	return Value;
}

template<class T>
inline void Vector<T>::Swap(int Index1, int Index2)
{
	assert(Index1 >= 0 && Index1 < m_End);
	assert(Index2 >= 0 && Index2 < m_End);
	T Temp = m_Data[Index1];
	m_Data[Index1] = m_Data[Index2];
	m_Data[Index2] = Temp;
}

template<class T>
inline void Vector<T>::SetValue(int Index, T Value)
{
	assert(Index >= 0 && Index < m_End);
	if(Index >= 0 && Index < m_End)
	{
		m_Data[Index] = Value;
	}
}

template<class T>
inline T Vector<T>::GetAt(int Index)
{
	assert(Index >= 0 && Index < m_End);
	T Value;
	if(Index >= 0 && Index < m_End)
	{
		Value = m_Data[Index];
	}
	return Value;
}

template<class T>
inline T Vector<T>::operator[](int Index)
{
	return GetAt(Index);
}

template<class T>
int Vector<T>::Size()
{
	return m_End;
}

template<class T>
int Vector<T>::Capacity()
{
	return m_Count;
}

template<class T>
bool Vector<T>::GrowBy(int Count)
{
	// Grow data by Count elements
	if(m_Data == NULL)
	{
		assert(m_Count == 0 && m_End == 0);
	}
	else
	{
		assert(Count > m_Count);
	}
	T *NewData = new T[Count];
	for(int x = 0; x < m_End; x++)
	{
		NewData[x] = m_Data[x];
	}
	delete[] m_Data;
	m_Data = NewData;
	m_Count = Count;
	return true;
}

template<class T>
bool Vector<T>::Grow()
{
	// Double the size of Data
	int NewSize = m_Count * 2;
	if(NewSize == 0)
	{
		NewSize = 5;
	}
	return GrowBy(NewSize);
}

#endif