#include <iostream>
using namespace std;
int main() {
    int n=8;
    int originalArray[n]={1,2,3,4,5,6,7,8};
    int reversedArray[n];
    for (int i = 0; i < n; ++i) {
	reversedArray[i] = originalArray[n - 1 - i];
    }
    cout << "Original Array: ";
    for (int i = 0; i < n; ++i) {        
	cout << originalArray[i] << " ";
    }
    cout << endl;
    cout << "Reversed Array: ";
    for (int i = 0; i < n; ++i) {
    cout << reversedArray[i] << " ";
    }
    cout << endl;
    return 0;
}