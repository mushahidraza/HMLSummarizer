#include<iostream>
#include "DynamicSafeArray.cpp"
using namespace std;

class sentence
{
	private:
		int noWords;					//no of words sentence contains
		DynamicSafeArray<char> sent;	//USING DSA DATA STRUCTURE
		int WordsFreq[10000];			//frequency will be stored using hashing methods
		double weightedFreq;		
		
	public:
		sentence();
		sentence(const sentence& sen);	
		sentence& operator=(const sentence&s);		
		void set(char s[] , int len , int noWords);
		bool operator==(const sentence &Sent);
		int GetHashKey(char s[] , int len);		
		void SetFreq();
		bool IsStopWord(char arr[],int len);
		bool IsCompleteWord(char sign);
		void CalcWeightFreq();
		double GetWeightedFreq();		
		void Display();
		void strcopy(string&);
		void outputstats(ofstream &file);
		void outputinfile(ofstream &file);
};
