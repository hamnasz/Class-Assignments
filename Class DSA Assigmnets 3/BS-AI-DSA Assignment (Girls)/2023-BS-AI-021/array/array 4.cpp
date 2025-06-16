#include <iostream>
using namespace std;
int main() {
    const int size = 10;
    char characters[size];

    cout << "Enter " << size << " characters:" <<endl;
    for (int i = 0; i < size; ++i) {
       cin >> characters[i];
    }

    char target;
    cout << "Enter a character to count: ";
    cin >> target;

    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (characters[i] == target) {
            count++;
        }
    }

    cout << "The character '" << target << "' appears " << count << " time(s) in the array." <<endl;

    return 0;
}
