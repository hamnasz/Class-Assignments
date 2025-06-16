#include <iostream>
using namespace std;

int main() {
   int size=5;
    char arr[5];
    char target;
    int count = 0;

    cout << "Enter " << size << " characters: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Enter character to search: ";
    cin >> target;

    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            count++;
        }
    }

    cout << "Array Elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Character '" << target << "' appears " << count << " times." << endl;

    return 0;
}
