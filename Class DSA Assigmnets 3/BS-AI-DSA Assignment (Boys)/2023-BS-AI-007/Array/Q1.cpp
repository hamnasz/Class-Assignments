#include <iostream>
using namespace std;

int main(){
	int size = 10;
	int arr[size] = {4,6,12,64,82,4,65,42,12,10};
	int sum = 0;
	
	for(int i = 0; i<size; i++){
		sum += arr[i];
	}
	float avg = float(sum)/float(size);
	cout<<sum<<endl;
	cout<<avg;
}