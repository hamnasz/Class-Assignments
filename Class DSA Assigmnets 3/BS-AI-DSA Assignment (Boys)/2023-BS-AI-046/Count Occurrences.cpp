#include <iostream>
using namespace std;

int main() {
    char array[6] = {'a', 'b', 'c', 'a', 'b', 'a'};
    char target;
    cout << "Enter a character to count: ";
    cin >> target;

    int count = 0;
    for (char c : array) {
        if (c == target) count++;
    }
    cout << "The character '" << target << "' appears " << count << " times." << endl;
    return 0;
}
