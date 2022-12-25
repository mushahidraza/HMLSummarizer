#ifndef	DYNAMICSAFEARRAY_H
#define DYNAMICSAFEARRAY_H

using namespace std;

template <class T>
class DynamicSafeArray
{	
	private:
		int size;
		T * Data;	
	public:
		 int length;
	     DynamicSafeArray();
	     DynamicSafeArray(int Size);
		 DynamicSafeArray(const DynamicSafeArray<T>& rhs);
	     ~DynamicSafeArray();
	     int Size();
	     void ReSize(int nSize);
		 DynamicSafeArray<T>& operator = (const DynamicSafeArray<T>& rhs);
		 T& operator [](int i);
		 const T& operator[](int i) const;
		 bool operator == (const DynamicSafeArray<T>& rhs);
		 int strlength();
		 void strcpy(char Arr[]);
};

#endif

