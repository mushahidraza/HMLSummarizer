#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include "DynamicSafeArray.h"

using namespace std;

template <class T>
DynamicSafeArray<T>::DynamicSafeArray ()
	{
		Data= NULL;
		size=0;
		length=0;
	}
	
template <class T>
int DynamicSafeArray<T>::Size ()
	{
		return size;
	}
	
//lval
template <class T>
T& DynamicSafeArray<T>::operator [] (int i){   
    if (i>=0 && i<size)
    return (*(Data+i));
    
}	

//rval
template <class T>
const T& DynamicSafeArray<T>::operator [] (int i) const {   
    if (i>=0 && i<size)
    	return (*(Data+i));
}	
	


template <class T>
DynamicSafeArray<T>::DynamicSafeArray (int Size)
	{
		Data=new T[Size];
		size=Size;
		length=0;
	}
	
template <class T>
DynamicSafeArray<T>::~DynamicSafeArray(){

 if (Data != 0)
 {
 	delete [] Data;
 	Data=0;
 	size=0;
 	length = 0;
 }

}
	
template<class T>
DynamicSafeArray<T>::DynamicSafeArray(const DynamicSafeArray<T> & rhs)
{			
	this->size= rhs.size;
	this->length = rhs.length;
	this->Data= new T[size];
	memcpy(this->Data,rhs.Data,(sizeof(T)*size));
}

template<class T>
DynamicSafeArray<T>& DynamicSafeArray<T>:: operator=( const DynamicSafeArray<T> & rhs)
{
    if (this != &rhs)
    {   
    	if(Data)
    	{
			delete this->Data;
    		this->Data = NULL;
    		this->size = 0;    	
			this->length = 0;	
		}
		int s=rhs.size; 
    	this->size=s;
    	this->length = rhs.length;
		this->Data= new T[s];
    	memcpy(this->Data,rhs.Data, sizeof(T)*s);
    }
    return (*this);
         
}

template <class T>
void DynamicSafeArray<T>::ReSize(int nSize)
{
	if (size != nSize )  
	{
		T * temp= new T[size]; 	
	    for(int i=0; i<size ; i++)
		{
	     	temp[i]= *(Data+i);
	    }
	    delete[] Data;
	    Data=0;    
		Data = new T[nSize];
		memset(this->Data, 0, sizeof(T)*nSize);

		for(int i=0; i<size ; i++)
		{
			*(Data+i)=temp[i];
		}
	    size= nSize;
	    delete [] temp;
	    temp=0;
	}				
}

template <class T>
bool DynamicSafeArray<T>::operator == ( const DynamicSafeArray<T>&  rhs)
	{
		bool check;
		if(size==rhs.size)
			for (int count=0;count<rhs.size;count++)
			{
				if ( Data[count]==rhs.Data[count])
					check=true;	
				else
					check=false;
				if(check==false)
					break;
			}
		else check=false;
		return check;
	}

template <class T>
int DynamicSafeArray<T>::strlength()
	{
		int i=0;
		while(i<this->size && Data[i]!='\0')
		{
			i++;
		}
		this->length=i;
		return i;
	}

template <class T>
void DynamicSafeArray<T>::strcpy(char Arr[])
	{
		int i=0;
		int len = strlen(Arr);
		while(Arr[i]!='\0' && i<len)
		{
			Data[i]=Arr[i];
			i++;
		}
	}


