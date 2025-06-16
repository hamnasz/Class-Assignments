#include <iostream>
using namespace std;
int main() {
    int n=10;
    int originalArr[n]={1,2,3,4,5,6,7,8,2,1};
    int reversedArr[n];
    for (int i = 0; i < n; ++i) {
	reversedArr[i] = originalArr[n - 1 - i];
    }
    cout << "Original Array: ";
    for (int i = 0; i < n; ++i) {        
	cout << originalArr[i] << " ";
    }
    cout << endl;
    cout << "Reversed Array: ";
    for (int i = 0; i < n; ++i) {
    cout << reversedArr[i] << " ";
    }
    cout << endl;
    return 0;
}