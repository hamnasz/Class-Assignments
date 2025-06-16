#include <iostream>
using namespace std;
int main() {
    char array[] = "zoomer fiaz";
    char searchChar;
    cout << "Enter a character to search: ";
    cin >> searchChar;
    int count = 0;
    for (int i = 0; array[i] != '\0'; i++) {
        if (array[i] == searchChar) {
            count++;
        }
    }
    cout<< "Character '" <<searchChar<< "' appears " <<count<< " times." <<endl;
    return 0;
}
