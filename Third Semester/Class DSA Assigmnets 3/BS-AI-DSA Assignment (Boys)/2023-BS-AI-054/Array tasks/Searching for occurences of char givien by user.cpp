#include <iostream>
using namespace std;

int main() {
  
    char characters[] = {'a', 'b', 'c', 'a', 'd', 'e', 'a', 'f', 'b', 'a'};
    int arraySize = sizeof(characters) / sizeof(characters[0]);

    char searchChar;
    int count = 0;


    cout << "Enter a character to search for: ";
    cin >> searchChar;

  
    for (int i = 0; i < arraySize; i++) {
        if (characters[i] == searchChar) {
            count++;
        }
    }

   
    cout << "The character '" << searchChar << "' appears " << count << " times in the array." << endl;

    return 0;
}
