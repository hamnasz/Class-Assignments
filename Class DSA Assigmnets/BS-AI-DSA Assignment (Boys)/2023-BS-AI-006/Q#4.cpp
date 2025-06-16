#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {12, 22, 33, 44, 55};

    cout << "Numbers in the array:\n";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << endl;
    }

    return 0;
}