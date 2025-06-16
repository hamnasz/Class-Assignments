#include <iostream>
using namespace std;

void maxEle(int arr[], int size){
	int max = INT_MIN;
	for(int i = 0; i<size; i++){
		if(arr[i]>max){
			max = arr[i];
		}
	}
	cout<<"Max: "<<max;
}

int main(){
	int s = 5;
	int myArr[] = {23, 7, 75, 43, 32};
	
	maxEle(myArr,s);
}