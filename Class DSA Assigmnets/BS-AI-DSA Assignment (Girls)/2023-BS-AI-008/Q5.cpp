#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int fixedValue = 100;

    for (int i = 0; i < 5; i++) {
        cout << "100 - " << arr[i] << " = " << (fixedValue - arr[i]) << endl;
    }

    return 0;
}

