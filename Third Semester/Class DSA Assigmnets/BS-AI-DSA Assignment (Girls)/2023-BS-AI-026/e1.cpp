#include <iostream>
using namespace std;

int main() {
    // Create an array of 5 fruits
    string fruits[5] = {"Apple", "Banana", "Orange", "Mango", "Grapes"};

    // Display the fruits
    cout << "List of fruits:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << fruits[i] << endl;
    }

    return 0;
}
