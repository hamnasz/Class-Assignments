#include<iostream>
using namespace std;
int main () {
	int arr[10], i, sum=0;
	float avg=0;
	for (i=0; i<10; i++){
		cout<<"enter elements: ";
		cin>>arr[i];
		sum= sum+arr[i];
	}
	avg= sum/10;
	cout<<"sum:"<<sum<<endl;
	cout<<"average:"<<avg<<endl;
}
