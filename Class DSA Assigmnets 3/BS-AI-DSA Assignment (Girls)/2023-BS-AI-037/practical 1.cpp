#include <iostream>
using namespace std;

int main() {
   
    int numbers[10] = {5, 8, 12, 20, 3, 15, 7, 10, 25, 18};
    int sum = 0;
    double average;

    
    for (int i = 0; i < 10; i++) {
        sum += numbers[i];
    }

   
    average = static_cast<double>(sum) / 10;


    cout << "Array: ";
    for (int i = 0; i < 10; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "Sum of array elements: " << sum << endl;
    cout << "Average of array elements: " << average << endl;

    return 0;
}