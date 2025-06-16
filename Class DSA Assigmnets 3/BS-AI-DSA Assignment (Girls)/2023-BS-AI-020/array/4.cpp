#include <iostream>
using namespace std;

int main() {
    char arr[100];
    char ch;
    int count = 0;

    cout << "Enter a string of characters (max 100):\n";
    cin >> arr;
    
    cout << "Enter the character to count:\n";
    cin >> ch;

    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == ch) {
            count++;
        }
    }

    cout << "The character '" << ch << "' appears " << count << " times." << endl;

    return 0;
}
