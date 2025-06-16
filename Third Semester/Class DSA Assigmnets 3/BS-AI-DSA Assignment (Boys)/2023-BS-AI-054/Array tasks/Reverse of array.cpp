#include <iostream>
using namespace std;
int main() 
{
   	
	int n;
    
	cout << "Enter the size of the array: ";
    cin >> n;
   
    int originalArray[n];
    int reversedArray[n];
   
    cout << "Enter elements of the array: ";
    for (int i = 0; i < n; ++i) {
    cin >> originalArray[i];
    }
   
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