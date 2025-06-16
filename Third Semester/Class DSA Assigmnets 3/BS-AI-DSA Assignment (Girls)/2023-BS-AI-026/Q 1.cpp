#include <iostream>
using namespace std;

int main() {
	int sum=0;
	int avg=0;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
   avg =  sum / 10;
    cout << "Array Elements: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Sum of Elements: " << sum << endl;
    cout << "Average of Elements: " << avg << endl;
   
}
