#include <iostream>
using namespace std;

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    int sum = 0;
    double average;

    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    average = sum / 10.0; 

    cout << "Sum: " << sum << "\n";
    cout << "Average: " << average << "\n";

    return 0;
}
