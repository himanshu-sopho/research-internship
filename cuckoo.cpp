#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

int count=0;
int hash=11;

int insert_2(vector<int> &a,vector<int> &b,vector<int> &c,int number);
void rehash(vector<int> &a,vector<int> &b,vector<int> &c);

int insert_1(vector<int> &a,vector<int> &b,vector<int> &c,int number)
{
	
	if (count==(2*hash+1))
	{
		cout << "Need to rehash";
		hash =hash + 2 ;
		rehash(a,b,c);
		return 0;
	}
	int key = (number)%hash;
	if (a[key]==0)
	{
		a[key]=number;
	}
	else 
	{
		int temp=a[key];
		a[key]=number;
		count++;
		insert_2(a,b,c,temp);
	}
}

int insert_2(vector<int> &a,vector<int> &b,vector<int> &c,int number)
{
	if (count==(2*hash+1))
	{
		cout<<"need to rehash";
		hash =hash + 2;
		rehash(a,b,c);
		return 0;
	}
	int key = (number/hash)%hash;
	if (b[key]==0)
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
void rehash(vector<int> &a,vector<int> &b,vector<int> &c)
{
				a.resize(hash);
				b.resize(hash);
				for (int i=0;i<hash;i++)
				{
					a[i]=0;
					b[i]=0;
				}
				for (int i=0;i<c.size();i++)
				{
					int temp=c[i];
					insert_1(a,b,c,temp);
				}
}

int main()
{
	vector<int> a;//=new int[hash];
	vector<int> b;
	a.resize(11);
	b.resize(11);//=new int[hash];
	vector<int> c;
	int choice;
	int number;
	while(1)
	{
		cout<< endl<<"Choose the option 1--Insert 0--Exit"<<endl;
		cin >> choice;
		if (choice==1)
		{
			cout<<"Enter the number ";
			cin>> number;
			count=0;
			c.push_back(number);
			insert_1(a,b,c,number);
			
		}
		else if (choice==0)
		{
			cout<<endl;
			for (int i=0;i<hash;i++)
			{
				cout<<a[i]<<"          "<<b[i]<<endl;
			}
			exit(0);
		}
		else 
		{
			cout<<"action not found"<<endl;
		} 
	}	
}
