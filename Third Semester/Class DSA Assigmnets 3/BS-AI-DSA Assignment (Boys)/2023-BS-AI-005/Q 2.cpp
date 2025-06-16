#include <iostream>
using namespace std;
int main() {
    int array[5];
    cout << "Enter 5 integers: ";
    for (int i = 0; i < 5; i++) {
        cin >> array[i];
    }
    int max = array[0];
    int min = array[0];
    for (int i = 1; i < 5; i++) {
        if (array[i] > max) {
            max = array[i];
        }
        if (array[i] < min) {
            min = array[i];
        }
    }
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << array[i] << " ";
    }
    cout <<endl;
    cout << "Maximum value: " << max <<endl;
    cout << "Minimum value: " << min <<endl;

    return 0;
}