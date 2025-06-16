#include <iostream>
using namespace std;

int main() {
    const int SIZE = 8; 
    char arr[SIZE] = {'a', 'b', 'c', 'a', 'd', 'a', 'e', 'f'};
    char target;
    int count = 0;

    cout << "Enter a character to count: ";
    cin >> target;

    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == target) {
            count++;
        }
    }

    cout << "The character '" << target << "' appears " << count << " times in the array.\n";

    return 0;
}
