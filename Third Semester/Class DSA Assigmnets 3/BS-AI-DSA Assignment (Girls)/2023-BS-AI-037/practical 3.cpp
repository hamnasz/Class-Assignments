#include <iostream>
using namespace std;

int main() {
    // Create an array of 8 integers
    int numbers[8] = {2, 5, 8, 12, 19, 25, 30, 35};
    
    // Display the original array
    cout << "Original array: ";
    for (int i = 0; i < 8; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    
    // Reverse the array
    for (int i = 0; i < 4; i++) {
        // Swap the elements at positions i and (7 - i)
        int temp = numbers[i];
        numbers[i] = numbers[7 - i];
        numbers[7 - i] = temp;
    }

    // Display the reversed array
    cout << "Reversed array: ";
    for (int i = 0; i < 8; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}