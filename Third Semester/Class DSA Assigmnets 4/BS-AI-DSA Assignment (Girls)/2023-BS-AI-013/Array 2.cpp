#include<iostream>
using namespace std;
int main(){
	int arr[5], i, max, min;
	cout<<"enter elements:";
	for(i=0; i<5; i++){
		cin>>arr[i];
	}
	max=min=arr[0];
	for(i=0; i<5; i++){
		if(max<arr[i])
			max=arr[i];
		if(min>arr[i])
			min=arr[i];
	}
	cout<<"Maximum :"<<max<<endl;
	cout<<"Minimum :"<<min<<endl;
}
