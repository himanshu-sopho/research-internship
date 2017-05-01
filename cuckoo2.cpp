#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;


int count=0;	//variable to count the number of recursive calls made by the insert functions required for the detection of rehashing
int hash=11;	//initially hash function uses 11 for modulo

int insert_2(vector<int> &a,vector<int> &b,vector<int> &c,int number);		//second hash function
void rehash(vector<int> &a,vector<int> &b,vector<int> &c);			//function to be called if infinite loop detected

int insert_1(vector<int> &a,vector<int> &b,vector<int> &c,int number)		//first hash function
{
	if (count>(2*hash+1))						//check for infinite loop
	{
		cout << "Need to rehash" << endl;
		hash =hash + 2 ;			//increments the hash value by 2 so that rehashing uses this hash value 
		count=0; 
		cout << "Hash-->" << hash << endl;	
		rehash(a,b,c);							//rehashes
		return 0;
	}
	int key = (number)%hash;						//key to decide the bucket 
	
	if (a[key]==0)						//if there is no element exisiting already in that bucket
	{
		a[key]=number;
	}
	else 							//otherwise
	{
		int temp=a[key];
		a[key]=number;
		count++;
		insert_2(a,b,c,temp);				//second function called if bucket is occupied  
	}
}

int insert_2(vector<int> &a,vector<int> &b,vector<int> &c,int number)		//second hash function 
{
	if (count>(2*hash+1))
	{
		cout<<"Need to rehash";
		hash =hash + 2;
		count=0;
		rehash(a,b,c);
		return 0;
	}
	int key = (number/hash)%hash;				//key value
	
	if (b[key]==0)						//vice versa of previous function
	{
		b[key]=number;
	}
	else 
	{
		int temp=b[key];
		b[key]=number;
		count++;
		insert_1(a,b,c,temp);				
	}
}
void rehash(vector<int> &a,vector<int> &b,vector<int> &c)		//function for infinite loop(rehashing) 
{
				a.resize(hash);				//resizes the original vector a since reahshing requires new size
				b.resize(hash);				//resizes the original vector b
				for (int i=0;i<hash;i++)		//re initialize the vectors 
				{
					a[i]=0;
					b[i]=0;
				}
				for (int i=0;i<c.size();i++)		//inserts all the element back into the new hash tables  
				{
					int temp=c[i];
					count=0;
					insert_1(a,b,c,temp);
				}
}

void display(vector<int> &a,vector<int> &b)			//displays the hashtable containing 2 vectors 
{
cout << "The two hash tables are" << endl;

	cout<<endl;
	for (int i=0;i<hash;i++)
	{
	cout<<a[i]<<"\t\t"<<b[i]<<endl;
	}
}

int main()
{
	vector<int> a;					//first vector of the hashtable
	vector<int> b;					//first vector of the hashtable
	a.resize(hash);					
	b.resize(hash);
	vector<int> c;					//vector for storing all the entries separately(saves some time)
	int choice;
	int number;

	do
	{
	cout<< endl<<"Choose the option 1--Insert   2--to display  3--to Exit"<<endl;
	cin >> choice;									//input

	switch (choice)
		{
		case 1:
			cout<<"Enter the number ";
			cin>> number;
			count=0;
			c.push_back(number);					//ensures space optimality to some extent
			insert_1(a,b,c,number);
			break;
		case 2:
			display(a,b);
			break;
		case 3:
			exit (0);

		default:
			cout<<"action not found"<<endl;
		}

	}while (choice!=3);

}
