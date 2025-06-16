#include <iostream>
using namespace std;

int main() {
    char arr[10] = {'a', 'b', 'c', 'a', 'd', 'a', 'e', 'f', 'a', 'g'};
    char target;
    int count = 0;

    cout << "Enter a character to count its occurrences: ";
    cin >> target;

    for (int i = 0; i < 10; i++) {
        if (arr[i] == target) {
            count++;
        }
    }

    cout << "Number of occurrences of " << target << ": " << count << endl;

    return 0;
}
