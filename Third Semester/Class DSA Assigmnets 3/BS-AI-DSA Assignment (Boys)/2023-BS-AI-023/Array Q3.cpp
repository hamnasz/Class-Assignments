#include <iostream>
using namespace std;

int main() {
    int arr[8];
    cout << "Enter 8 integers: ";
    for(int i = 0; i < 8; i++) {
        cin >> arr[i];
    }
    cout << "Reversed array: ";
    for(int i = 7; i >= 0; i--) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
