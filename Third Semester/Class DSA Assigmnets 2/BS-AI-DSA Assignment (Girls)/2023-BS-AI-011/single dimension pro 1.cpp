#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    double average;

    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    average = sum / 5.0; // Calculate average
    cout << "Average of array elements: " << average << endl;

    return 0;
}
