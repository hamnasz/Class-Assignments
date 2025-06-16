#include <iostream>
using namespace std;

int main() {
    int arr[5] = {11, 22, 33, 44, 55};
    cout << "Reversed array: ";
    for (int i = 4; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    return 0;
}
