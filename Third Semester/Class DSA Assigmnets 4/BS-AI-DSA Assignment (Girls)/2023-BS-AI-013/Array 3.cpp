#include<iostream>
using namespace std;
int main ()
{
	int arr[5], i;
	cout<<"enter elements: ";
	for (i=0; i<5; i++)
	{
		cin>>arr[i];
	}
	cout<<"\n Array in original order: \n";
	for (i=0; i<5; i++)
	cout<<arr[i]<<" ";
	cout<<"\n Array in reverse order: \n";
	for (i=4; i>=0; i--)
	cout<<arr[i]<<" ";
	return 0;
}
