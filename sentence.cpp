#include<iostream>
#include<string.h>
#include<cstring>
#include<fstream>
#include "sentence.h"
using namespace std;

char stopwords[200][20];
int noStop;
int maxFreq;
int GlobalFreqArray[10000]={0};
char EndSymbol[]={'.','?','!',':'};
char wordEndSymbol[]={' ',',','.'};

//^GLOBAL VARIABLES


/*-----------------------------------------------------------------------------*/

sentence::sentence()
{
	sent.ReSize(100000);
}

/*-----------------------------------------------------------------------------*/

//kind of a copy-utility-function
void sentence::set(char s[] , int len , int noWords)
{
	sent.ReSize(100000);
	sent.strcpy(s);
	this->noWords = noWords;
	memset(WordsFreq,0,sizeof(int)*1000);	// intializing WordFreq Array with 0
	weightedFreq = 0;
}

/*-----------------------------------------------------------------------------*/

sentence::sentence(const sentence& sent2) 
{ 
	this->noWords = sent2.noWords;
	this->weightedFreq = sent2.weightedFreq;
	for(int i = 0; i<10000;i++)
	{
		WordsFreq[i] = sent2.WordsFreq[i];
	}
	sent = sent2.sent;
	//strcpy(this->sent, sent2.sent);
}

/*-----------------------------------------------------------------------------*/

sentence& sentence:: operator=(const sentence &sent2) 
{ 
    this->noWords = sent2.noWords;
	this->weightedFreq = sent2.weightedFreq;
	for(int i = 0; i<10000;i++)
	{
		WordsFreq[i] = sent2.WordsFreq[i];
	} 
	sent = sent2.sent;
	//strcpy(this->sent, sent2.sent);
	return *this;
}

/*-----------------------------------------------------------------------------*/
    
//Overloaded == Operator
bool sentence::operator==(const sentence &Sent)
{
	if(this->noWords != Sent.noWords)
		return false;
		
	int length = sent.strlength();
	int length2 = Sent.sent.length;
	if( length != length2)
		return false;
			
	for(int i=0 ; i<10000 ; ++i)
	{
		if(this->WordsFreq[i] != Sent.WordsFreq[i])
			return false;
	}
			
	for(int i=0 ; i<length ;i++)
		if(sent[i] != Sent.sent[i])
			return false;
					
	return true;		
}

/*-----------------------------------------------------------------------------*/

//Hashing Function
int sentence::GetHashKey(char s[] , int len)		//This Function would be global not a member function
{
	int key = 0;
	for(int i=0 ; i<len ; i++)
	{
		if(s[i] > 96)
			key += ((s[i]-97)*(i+1));
		else
			key += ((s[i]-65)*(i+1));
	}
		return key%10000;
}
		
/*-----------------------------------------------------------------------------*/
				
void sentence::SetFreq()
{
	char temp[100] = "";
	int length = sent.strlength();
	for(int i=0,k=0; i<length ;i++)
	{
		if(!IsCompleteWord(sent[i]))
			temp[k] = sent[i];
				
		if(i == length-1 || IsCompleteWord(sent[i]))
		{
			if(i == length-1)
				k++;
			temp[k] = '\0';
					
			int key = GetHashKey(temp,k);
					
			if(!IsStopWord(temp,k))
			{
				this->WordsFreq[key]++;
				GlobalFreqArray[key]++;
						
				if(GlobalFreqArray[key] > ::maxFreq)
					::maxFreq = GlobalFreqArray[key];
			}
					
			k = -1;
			strcpy(temp,"");
		}
		k++;	
	}
}

/*-----------------------------------------------------------------------------*/

bool sentence::IsStopWord(char arr[],int len)	
{
	for(int i=0;i<noStop;i++)
	{
		if(stopwords[i][0] == arr[0] || stopwords[i][0]-32 == arr[0])	//checking whether first letter in UPPER or LOWER CASE
		if(len == strlen(stopwords[i]))
		{
			int j;
			for(j=1 ; j<len ; j++)
				if(arr[j] != stopwords[i][j] )
					break;
			if(j == len)
				return true;			
		}	
	}
	return false;	
}

/*-----------------------------------------------------------------------------*/

bool sentence::IsCompleteWord(char sign)
{
	for(int i=0; i<3 ;i++)
		if(sign == wordEndSymbol[i])
				return true;
	return false;				
}

/*-----------------------------------------------------------------------------*/

double sentence::GetWeightedFreq()
{
		return weightedFreq;
}

/*-----------------------------------------------------------------------------*/

void sentence::CalcWeightFreq()
{
	this->weightedFreq = 0;
	for(int i=0 ; i < 10000 ; i++)
	{
		if(this->WordsFreq[i] > 0)
		{
			this->weightedFreq += (double(GlobalFreqArray[i] * WordsFreq[i]))/::maxFreq;
		}
	}
}

/*-----------------------------------------------------------------------------*/

void sentence::Display()
	{
		int length = sent.strlength();
		for(int i=0; i<length && sent[i]!='\0';i++)
		{
			cout<<sent[i];
		}
	}
	
/*-----------------------------------------------------------------------------*/


void sentence::strcopy(string &str)
{
	//str = this->sent;
}

/*-----------------------------------------------------------------------------*/

void sentence::outputstats(ofstream &file)
{	
	int length = sent.strlength();
	for(int i=0; i<length && sent[i]!='\0';i++)
	{
		file << sent[i];
	}
	file << " WF: " << weightedFreq << endl; 
}

/*-----------------------------------------------------------------------------*/

void sentence::outputinfile(ofstream &file)
{	
	int length = sent.strlength();
	for(int i=0; i<length && sent[i]!='\0';i++)
	{
		file << sent[i];
	}
	file << endl; 
}

/*-----------------------------THE-END------------------------------------------*/

