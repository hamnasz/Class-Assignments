#include<iostream>
using namespace std;
int main ()
{
	int arr[5], i;
	for (i=0; i<5; i++)
	{
		cout<<"enter elements: ";
		cin>>arr[i];
	}
	cout<<"\n array in original order: \n";
	for (i=0; i<5; i++)
	cout<<arr[i]<<" ";
	cout<<"\n array in reverse order: \n";
	for (i=4; i>=0; i--)
	cout<<arr[i]<<" ";
}
