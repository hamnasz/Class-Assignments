#include <iostream>
using namespace std;

int main() {
    // Initialize an array with 5 integers
    int numbers[5] = {10, 20, 30, 40, 50};
    
    cout << "Array Elements:" << endl;
    
    // Using a for loop to display array elements
    for(int i = 0; i < 5; i++) {
        cout << "Element at index " << i << ": " << numbers[i] << endl;
    }
    
    return 0;
}
