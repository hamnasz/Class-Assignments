#include <iostream>
using namespace std;

int main(){
	int size = 8;
	int arr[size] = {4,6,12,64,82,4,65,42};
	
	for(int i = size-1; i>=0; i--){
		cout<<arr[i]<<" ";
	}
}