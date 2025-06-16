#include<iostream>
using namespace std;
int main(){
	int arr[5], i, max, min;
	for(i=0; i<5; i++){
		cout<<"enter elements:";
		cin>>arr[i];
	}
	max=min=arr[0];
	for(i=0; i<5; i++){
		if(max<arr[i])
			max=arr[i];
		if(min>arr[i])
			min=arr[i];
	}
	cout<<"maximum number:"<<max<<endl;
	cout<<"minimum number:"<<min<<endl;
}
