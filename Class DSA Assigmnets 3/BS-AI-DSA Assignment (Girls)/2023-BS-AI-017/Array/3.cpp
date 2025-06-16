#include <iostream>
using namespace std;

int main() {
    int size = 8;
    int initialArray[size] = {1, 2, 3, 4, 5, 6, 7, 8};
    int reversedArray[size];

    for (int i = 0; i < size; ++i) {
        reversedArray[i] = initialArray[size - 1 - i];
    }

    cout << "Original Array: ";
    for (int i = 0; i < size; ++i) {        
        cout << initialArray[i] << " ";
    }
    cout << endl;

    cout << "Reversed Array: ";
    for (int i = 0; i < size; ++i) {
        cout << reversedArray[i] << " ";
    }
    cout << endl;

    return 0;
}
