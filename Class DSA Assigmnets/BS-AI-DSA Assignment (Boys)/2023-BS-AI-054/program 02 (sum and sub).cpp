#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    int sub=0;

    for(int i = 0; i < 5; i++) {
        sum += arr[i];
    }
    
    for(int i=0;i<5;i++){
    	sub-=arr[i];
	}

    cout << "Sum of array elements: " << sum << endl;
    cout<<"The Diff of array elements: "<< sub<<endl;
	return 0;
}
