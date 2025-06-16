#include <iostream>
using namespace std;

int main() {
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    cout << "Original Array: ";
    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Reverse array
    cout << "Reversed Array: ";
    for (int i = 7; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
