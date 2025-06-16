#include <iostream>
using namespace std;

int main() {
    char arr[8] = {'a', 'b', 'c', 'a', 'd', 'e', 'a', 'f'}; // Example array
    char target;
    int count = 0;

    // Get the character to search for from the user
    cout << "Enter a character to search for: ";
    cin >> target;

    // Count occurrences of the target character in the array
    for (int i = 0; i < 8; i++) {
        if (arr[i] == target) {
            count++;
        }
    }

    // Display the result
    cout << "The character '" << target << "' appears " << count << " times in the array." << endl;

    return 0;
}
