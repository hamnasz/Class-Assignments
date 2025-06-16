#include <iostream>
using namespace std;
int main() {
    int array[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    cout << "Original array: ";
    for (int i = 0; i < 8; i++) {
        cout << array[i] << " ";
    }
    cout <<endl;
    int start = 0;
    int end = 7;
    while (start < end) {
        swap(array[start], array[end]);
        start++;
        end--;
    }
    cout << "Reversed array: ";
    for (int i = 0; i < 8; i++) {
    cout << array[i] << " ";
    }
    cout <<endl;
    return 0;
}