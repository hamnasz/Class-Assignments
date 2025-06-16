#include <iostream>
using namespace std;

int main() {
    int laiba[] = {1, 2, 3, 4, 5};  // Initialize an array
    int size = sizeof(laiba) / sizeof(laiba[0]);

    cout << "Elements in the array: ";
    for (int i = 0; i < size; i++) {
        cout << laiba[i] << " ";
    }

    return 0;
}
