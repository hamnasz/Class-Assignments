#include <iostream>
using namespace std;

int main() {
    // Create an array of characters
    char array[10];
    
    // Input values for the array
    cout << "Enter 10 characters: ";
    for (int i = 0; i < 10; i++) {
        cin >> array[i];
    }

    // Input the character to search for
    char searchChar;
    cout << "Enter a character to count: ";
    cin >> searchChar;

    // Count occurrences of the specified character
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (array[i] == searchChar) {
            count++;
        }
    }

    // Display the result
    cout << "The character '" << searchChar << "' appears " << count << " time(s) in the array." << endl;

    return 0;
}

