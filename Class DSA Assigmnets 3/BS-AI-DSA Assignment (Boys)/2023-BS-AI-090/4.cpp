#include <iostream>
using namespace std;

int main() {
    char arr[] = {'a', 'b', 'c', 'a', 'd', 'a', 'e'};
    char charToFind;
    int count = 0;

    cout << "Enter character to count: ";
    cin >> charToFind;

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        if (arr[i] == charToFind) {
            count++;
        }
    }

    cout << "Character " << charToFind << " appears " << count << " times." << endl;

    return 0;
}
