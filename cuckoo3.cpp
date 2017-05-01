#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;


int count=0;	//variable to count the number of recursive calls made by the insert functions required for the detection of rehashing
int hash=11;	//initially hash function uses 11 for modulo
int n,k;

void rehash(vector<vector<int> > &a,vector<int> &c);			//function to be called if infinite loop detected

int insert_1(vector<vector<int> > &a,vector<int> &c,int number)		//first hash function
{
	if (count>(n*hash+1))						//check for infinite loop
	{
		cout << "Need to rehash" << endl;
		hash =hash * 2 ;			//doubles the hash value by 2 so that rehashing uses this hash value 
		count=0; 
		cout << "Hash-->" << hash << endl;	
		rehash(a,c);							//rehashes
		return 0;
	}
	int key = (number*(k+1)*13)%hash;						//key to decide the bucket 
	
	if (a[k][key]==0)						//if there is no element exisiting already in that bucket
	{
		a[k][key]=number;
	}
	else 							//otherwise
	{
		int temp=a[k][key];
		a[k][key]=number;
		count++;
		k=(k+1)%n;
		insert_1(a,c,temp);				//second function called if bucket is occupied  
	}
}


void rehash(vector<vector<int> > &a,vector<int> &c)		//function for infinite loop(rehashing) 
{
			for (int i=0;i<n;i++)
				a[i].resize(hash);			//resizes the original vector a since reahshing requires new size
							//resizes the original vector b
				for (int i=0;i<n;i++)		//re initialize the vectors 
				{
					for (int j=0;j<hash;j++)
						a[i][j]=0;
					
				}
				for (int i=0;i<c.size();i++)		//inserts all the element back into the new hash tables  
				{
					int temp=c[i];
					count=0;
					insert_1(a,c,temp);
				}
}

void display(vector<vector<int> > &a)			//displays the hashtable containing 2 vectors 
{
cout << "The two hash tables are" << endl;

	cout<<endl;
	for (int i=0;i<hash;i++)
	{
		for (int j=0;j<n;j++)
			cout<<a[j][i]<<"\t\t";
		cout<<endl;	
	}
}

int main()
{
	
	cout<< "Enter the number of hashtables";
	cin >> n;									//no of hashtables
	
	vector< vector<int> > vect(n);
	
	for (int i=0;i<n;i++)
	{
		vect[i].resize(hash);
	}
	

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
			k=0;
			insert_1(vect,c,number);
			break;
		case 2:
			display(vect);
			break;
		case 3:
			exit (0);

		default:
			cout<<"action not found"<<endl;
		}

	}while (choice!=3);

}
