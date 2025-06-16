#include <iostream>
using namespace std;

int main() {
    // Declare and initialize a 1D array
    int numbers[5] = {10, 20, 30, 40, 50};

    // Print the array elements
    cout << "Array elements: ";
    for (int i = 0; i < 5; ++i) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}