#include<iostream>
#include<string.h>
#include<cstring>
#include<fstream>
#include"sentence.cpp"

using namespace std;

/*-----------------------------------------------------------------------------*/

sentence *Sentences;
sentence *original;
sentence *FinalSummary;            	 	//Storing summary
int NoSent;
double *WeightedFreq;					//Array To Hold Weighted Frequency of Sentences

/*-----------------------------------------------------------------------------*/

int CalcNoSent(char arr[])				//No of Sentences in paragraph
{
	int count=0;
	int i=0;
	while(i<strlen(arr))
	{
		for(int j=0; j<4 ;j++)
		{
			if(arr[i] == EndSymbol[j])
				count++;	
		}
		i++;
	}
	return count;
}

/*-----------------------------------------------------------------------------*/

bool IsSentenceEnd(char sign)			//Check whether it is the end of a Sentence
{
	for(int i=0; i<4 ;i++)
	{
		if(sign == EndSymbol[i])
			return true;	
	}
	return false;		
}

/*-----------------------------------------------------------------------------*/

bool IsSentenceEnd(char arr[], int index)	//Check whether it is the end of a Sentence
{
	for(int i=0; i<4 ;i++)
		if(arr[index] == EndSymbol[i])
		{
			if(index>3)
				if(arr[index-2] == 'M' && arr[index-1] == 'r' || arr[index-3] == 'M' && arr[index-2] == 'r'&& arr[index-1] == 's' || arr[index-1] <= 'Z' && arr[index-1] >= 'A')
					return false;
			return true;
		}	
	return false;		
}

/*-----------------------------------------------------------------------------*/
	
void Split(char arr[] , int NoSent )		//Extraction of Sentence
{
	int k = 0;
	int noWords = 0;
	int index = 0;
	char *temp= new char[10000];						
	//char temp[200];
	
	for(int i=0 ; i<strlen(arr) ;i++)
	{
		if(arr[i] == ' ')		
			noWords++;
		
		if(IsSentenceEnd(arr[i]))	//if i arr[i] is ending symbol && letter before that is small
		{
			noWords++;
			temp[k] = '\0';
			
			Sentences[index].set(temp,k,noWords); 
			Sentences[index].SetFreq();
			k = 0;
			index++;
			noWords = 0;
		}
		else
			temp[k++] = arr[i];	
	}
}

/*-----------------------------------------------------------------------------*/

void mergeTwo(double a[],int l,int mid,int r)	//MergeSort Implement to Sort Sentences According To Their Weightage
{												//UtilityFunction						
	double temp[r-l+1];
	int k=0 , i=l , j=mid+1 ;
	while(i <= mid  &&  j <= r)
	{
		if(a[j] > a[i])
			temp[k++] = a[j++];
		else
			temp[k++] = a[i++];	
	}
	
	while(i <= mid)
		temp[k++] = a[i++];	
	
	while(j <= r)
		temp[k++] = a[j++];
	
	k=0;
	
	for(int i=l;i <= r; i++)
		a[i] = temp[k++];
}

/*-----------------------------------------------------------------------------*/

void mergeSort(double arr[],int l,int r)		//Recursive MergeSort
{
	if(r>l)
	{
		int mid=(l+r)/2;
		mergeSort(arr,l,mid);
		mergeSort(arr,mid+1,r);
		mergeTwo(arr,l,mid,r);
	}
}

/*-----------------------------------------------------------------------------*/

void CheckSimilar()						//Checking Whether Sentences Are Similar or Not
{
	for(int i=0; i<NoSent ;i++)
	{
		if(Sentences[i] == Sentences[i+1])
		{
			for(int j=i+1;j<NoSent;j++)
			{
				Sentences[j] = Sentences[j+1];
			}
			NoSent--;
		}
	}
}

/*-----------------------------------------------------------------------------*/

void ReadStopWords()				//Function To Read Stop Words From File	
{
	ifstream in;
	int i = 0;
	in.open("StopWords.txt");
	if(!in.is_open())
		cout<<"Error: Stop Words File Could Not Be Opened!"<<endl;
	else	
	{
		while(!in.eof())
			in>>stopwords[i++];
		noStop = i;
	}
	in.close();	
}

/*-----------------------------------------------------------------------------*/

void ReadTextFile(char arr[])					//Function To Read Original Text From File And Loading it in BUFFER
{
	string line,temp;
	ifstream input;
	input.open("file.txt");
	if(input.is_open())
	{
		while(!input.eof())
		{
			getline(input,temp);
			line+=temp;
		}
		input.close();
		char c='a'; int i=0;
		while(c !='\0')
		{
			c=line[i];
			arr[i]=c;
			i++;
		}
		c='\0';
		arr[i]=c;
	}
}

/*-----------------------------------------------------------------------------*/

void outputsummary(int k)				//Writing Summary To File
{
	ofstream file("summary.txt");
		for(int j = 0; j< k;j++)
			FinalSummary[j].outputinfile(file);
		file << endl << "Total Number Of Sentences In Summary: " << k;
	file.close();
}

/*-----------------------------------------------------------------------------*/

int main()								//DRIVER PROGRAM
{
	//char arr[10000];
	char *arr= new char [100000];
	//Reading Text From File in arr
	ReadTextFile(arr);

	//Outputting The Original Text
	cout<<"------Original Text------"<<endl<<endl;
	cout<<arr<<endl<<endl;
	
	//Reading Stop Words from A File To Remove Them
	ReadStopWords();
	
	//Calculating No of Sentences in the File and Weighing their Frequencies
	NoSent = CalcNoSent(arr);
	WeightedFreq = new double[NoSent];	//initializing Weighted Frequency [] Array  with No of Sentences
	
	//Outputting No. of Sentences
	cout<<"Total No. of Sentences: "<<NoSent<<endl<<endl;
	Sentences = new sentence [NoSent]; // initializing sentences with no of sentences
	//Splitting the text into sentences
	Split(arr,NoSent);
	
	original = new sentence [NoSent];
	for(int i = 0; i<NoSent;i++)
	{
		original[i] = Sentences[i];
	}
	
	//Checking if Similar Sentences
	CheckSimilar();
	
	
	//Calculating Weighted Frequencies
	for(int i=0 ; i < NoSent ; i++)
	{
		Sentences[i].CalcWeightFreq();	
		WeightedFreq[i] = Sentences[i].GetWeightedFreq();
	}
	
	
	int k = 0;	//variable to count final no of sentences in summary
	
	mergeSort(WeightedFreq,0,NoSent);	//Calling MergeSort
	
	//Outputting Statistics About Summary in File
	ofstream stats("statistics.txt");
	for(int i=0 ; i < NoSent ; i++)
	{
		//Sentences[i].Display();
		//Sentences[i].strcopy(FinalSummary[k++]);
		//cout<<" "<<Sentences[i].GetWeightedFreq()<<endl;
		Sentences[i].outputstats(stats);
	}
	stats.close();
	
	//Getting User Input About Summary Percentage
	double percentage;
	while(1)
	{	
		cout << "Enter Percentage Of Original Text You Want As Summary: ";
		cin >> percentage;
		if(percentage >=0 && percentage <=100)
			break;
	}
	percentage = (percentage/100)*float(NoSent);

		
	//Initializing FinalSummary with no of required sentences
	FinalSummary = new sentence [int(percentage) +1];

		
	//Outputting The Summary
	cout<<endl<<"-----Summary-----"<<endl;
	
	//Copying the required sentences in FinalSummary from Sentences & Printing Them
	for(int i = 0; i< NoSent; i++)
	{
		for(int j = 0; j< int(percentage); j++)
		{
			if(Sentences[i].GetWeightedFreq() == WeightedFreq[j])
			{
				Sentences[i].Display();
				FinalSummary[k++] = Sentences[i];
				break;
			}
		}
	}
	
	outputsummary(k);		//Calling Function To Write Summary To File
	
		cout << endl << "Total Number Of Sentences In Summary: " << k;
	return 0;
}

/*-------------------------------THE-END---------------------------------------*/





//SOME EXTRA BIT OF GARBAGE CODE

/*
	for(int i=0 ; i<int(percentage) ; i++)
	{
		for(int j=0 ; j<NoSent ; j++)
			if(Sentences[j].GetWeightedFreq() == WeightedFreq[i])	//Improvement Sort on the basis of WeightedFreq in Class
				{
					Sentences[j].Display();
					FinalSummary[k++] = Sentences[j];
					//Sentences[i].strcopy(FinalSummary[k++]);   //Saving summary in an array too
					break;
				}			
		cout<<"."<<endl;		
	}*/

//void sort()
//{
//	for(int i=0 ; i<NoSent; i++)
//	{
//		for(int j=0 ; j<NoSent-1 ;j++)
//		if(Sentences[j].GetWeightedFreq() < Sentences[j+1].GetWeightedFreq())
//		{
//			swap(Sentences[j],Sentences[j+1]);
//		}			
//	}
//}
