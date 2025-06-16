#include <iostream>
using namespace std;

int main() {
    int arr[5] = {12, 45, 7, 89, 23};
    int largest = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }

    cout << "The largest number is: " << largest << endl;

    return 0;
}

