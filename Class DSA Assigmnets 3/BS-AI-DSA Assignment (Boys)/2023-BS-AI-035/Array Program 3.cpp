#include <iostream>
using namespace std;

int main() {
    int integers[8];
    cout << "Enter 8 integers: ";
    
    for (int i = 0; i < 8; i++) {
        cin >> integers[i];
    }

    cout << "Reversed array: ";
    for (int i = 7; i >= 0; i--) {
        cout << integers[i] << " ";
    }
    cout << endl;

    return 0;
}
