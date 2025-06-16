#include <iostream>
using namespace std;

int main() {
    int arr[4] = {5, 10, 15, 20};
    arr[2] = 100;
    cout << "Modified array: ";
    for (int i = 0; i < 4; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
