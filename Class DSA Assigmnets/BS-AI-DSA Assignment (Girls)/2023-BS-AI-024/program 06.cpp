#include <iostream>
using namespace std;
int main()
{
	int arr[10],n,x,i ,y;
	cout<<"enter size: \n";
	cin>>n;
	cout<<"Enter value of array \n";
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
	}
	cout<<"enter value to search \n";
	cin>>x;
	for (int i=0;i<n;i++)
	if (arr[i]==x)
	{ 
	cout<<"number found at index \t"<<i<<endl;
	}
	if(i==n)
	{
	cout<<"number not found \t "<<endl;
    } 
		 return 0;
}