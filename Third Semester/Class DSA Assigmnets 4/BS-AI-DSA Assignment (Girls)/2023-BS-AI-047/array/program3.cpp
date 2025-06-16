#include <iostream>
using namespace std;

int main() {
    int laiba[] = {11, 22, 33, 44, 55};  // Initialize an array
    int size = sizeof(laiba) / sizeof(laiba[0]);

    cout << "Array in reverse order: ";
    for (int i = size - 1; i >= 0; i--) {
        cout << laiba[i] << " ";
    }

    return 0;
}
