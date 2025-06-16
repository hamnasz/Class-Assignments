#include <iostream>
using namespace std;

int main() {
    char characterArray[] = {'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'a', 'c'};
    int arraySize = sizeof(characterArray) / sizeof(characterArray[0]);
    
    char specificCharacter;
    cout << "Enter the character to count: ";
    cin >> specificCharacter;

    int count = 0;
    for (int i = 0; i < arraySize; ++i) {
        if (characterArray[i] == specificCharacter) {
            count++;
        }
    }
    cout << "The character '" << specificCharacter << "' appears " << count << " times in the array." << endl;

    return 0;
}
