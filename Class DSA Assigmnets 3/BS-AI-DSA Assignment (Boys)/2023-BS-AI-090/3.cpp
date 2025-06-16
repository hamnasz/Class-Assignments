#include <iostream>
using namespace std;

int main() {
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    for (int i = 0; i < 8 / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[8 - i - 1];
        arr[8 - i - 1] = temp;
    }

    cout << "Reversed array: ";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
