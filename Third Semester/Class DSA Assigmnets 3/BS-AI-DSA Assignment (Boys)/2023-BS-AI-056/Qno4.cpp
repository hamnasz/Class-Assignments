//4. Count Occurrences
#include <iostream>
using namespace std;
int main() {
    char arr[10];

    cout << "Enter 10 characters: ";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
    }

    char ch;
    cout << "Enter a character to count: ";
    cin >> ch;

    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (arr[i] == ch) {
            count++;
        }
    }

    cout << "The character '" << ch << "' appears " << count << " times." << endl;

    return 0;
}