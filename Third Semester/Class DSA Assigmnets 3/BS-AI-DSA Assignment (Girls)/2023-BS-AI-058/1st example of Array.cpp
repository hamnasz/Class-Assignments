#include <iostream>
using namespace std;

int main() {
    int arr[10] = {12, 45, 23, 67, 34, 89, 56, 10, 78, 90};
    int sum = 0;
    float average;

    // Calculate sum
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    // Calculate average
    average = sum / 10.0;

    // Output sum and average
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
