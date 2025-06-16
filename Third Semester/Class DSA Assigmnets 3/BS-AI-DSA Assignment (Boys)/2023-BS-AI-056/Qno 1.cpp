//1. Sum and Average
#include <iostream>
using namespace std;
int main() {
    int arr[10];

    cout << "Enter 10 integers: ";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }

    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    double average = sum / 10;

    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}