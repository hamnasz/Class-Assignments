#include <iostream>
using namespace std;

int main() {
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    cout << "Original array: ";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
    }

    cout << endl;

    int temp;
    for (int i = 0; i < 4; i++) {
        temp = arr[i];
        arr[i] = arr[7 - i];
        arr[7 - i] = temp;
    }

    cout << "Reversed array: ";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
