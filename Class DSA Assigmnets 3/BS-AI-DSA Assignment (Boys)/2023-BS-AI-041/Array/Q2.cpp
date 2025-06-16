#include <iostream>
using namespace std;

int main(){
	int size = 5;
	int arr[size] = {6,82,4,64,12};
	int max = arr[0];
	int min = arr[0];
	
	for(int i = 1; i<size; i++){
		if(arr[i]>max){
			max = arr[i];
		}
		if(arr[i]<min){
			min = arr[i];
		}
	}
	cout<<max<<endl;
	cout<<min<<endl;
}