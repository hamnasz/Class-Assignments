#include <iostream>
using namespace std;

void printArr(int arr[], int size){
	for(int i = 0; i<size; i++){
		cout<<arr[i]<<" ";
	}
}

int main(){
	int s = 5;
	int myArr[] = {23, 7, 43, 32, 75};
	
	printArr(myArr,s);
}