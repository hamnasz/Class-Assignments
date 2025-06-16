#include <iostream>
using namespace std;

int main() {
    char arr[] = {'a', 'b', 'c', 'a', 'd', 'e', 'f', 'a', 'g', 'h'};
    char searchChar;
    int count = 0;

    cout << "Enter the character to search: ";
    cin >> searchChar;

    // Count occurrences
    for (int i = 0; i < 10; i++) {
        if (arr[i] == searchChar) {
            count++;
        }
    }

    // Output count
    cout << "Character '" << searchChar << "' appears " << count << " times." << endl;

    return 0;
}
