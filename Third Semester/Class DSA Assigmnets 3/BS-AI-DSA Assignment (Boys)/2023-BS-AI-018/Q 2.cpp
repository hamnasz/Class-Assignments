#include <iostream>
using namespace std;

int main() {
    int arr[5];
    int max, min;

    cout << "Enter 5 integers: ";
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }

    max = min = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    cout << "Array Elements: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Maximum Value: " << max << endl;
    cout << "Minimum Value: " << min << endl;

    return 0;
}
