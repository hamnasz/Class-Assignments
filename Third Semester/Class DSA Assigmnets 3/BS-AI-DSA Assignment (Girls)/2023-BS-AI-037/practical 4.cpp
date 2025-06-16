#include <iostream>
using namespace std;

int main() {
    
    char characters[10] = {'a', 'b', 'c', 'a', 'd', 'e', 'a', 'f', 'g', 'a'};
    char target;
    int count = 0;

    
    cout << "Enter the character to count: ";
    cin >> target;

    
    for (int i = 0; i < 10; i++) {
        if (characters[i] == target) {
            count++;
        }
    }

    // Display the result
    cout << "The character '" << target << "' appears " << count << " times in the array." << endl;

    return 0;
}
