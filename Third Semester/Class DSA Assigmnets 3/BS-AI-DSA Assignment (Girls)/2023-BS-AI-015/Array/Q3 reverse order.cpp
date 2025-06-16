#include<iostream>
using namespace std;
int main ()
{
	int arr[8], i;
	for (i=0; i<8; i++)
	{
		cout<<"enter elements: ";
		cin>>arr[i];
	}
	cout<<"\n array in original order: \n";
	for (i=0; i<8; i++)
	cout<<arr[i]<<" ";
	cout<<"\n array in reverse order: \n";
	for (i=7; i>=0; i--)
	cout<<arr[i]<<" ";
	return 0;
}
