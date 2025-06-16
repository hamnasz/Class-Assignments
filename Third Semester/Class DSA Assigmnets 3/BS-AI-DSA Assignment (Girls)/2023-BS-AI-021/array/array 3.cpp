#include <iostream>
using namespace std;
int main() {
    int numbers[8];

    cout << "Enter 8 integers:" <<endl;
    for (int i = 0; i < 8; ++i) {
        cin >> numbers[i];
    }

    for (int i = 0; i < 4; ++i) {
        int temp = numbers[i];
        numbers[i] = numbers[7 - i];
        numbers[7 - i] = temp;
    }

    cout << "Reversed array:" <<endl;
    for (int i = 0; i < 8; ++i) {
        cout << numbers[i] << " ";
    }
    cout <<endl;

    return 0;
}
