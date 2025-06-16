//- Write a program to initialize an array of integers and print all the elements.
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};  // Initializing an array
    int length = 5;  // Define the length manually

    cout << "Array elements are: ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
