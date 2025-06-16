#include <iostream>
using namespace std;

int main() {
    string cricketers[4]; // Create an array to store cricketers' names

    cout << "Enter the names of your favorite cricketers: " << endl;
    for (int i = 0; i < 4; i++) {
        cin >> cricketers[i]; // Read names from user input
    }

    cout << "Your favorite cricketers are: ";
    for (int i = 0; i < 4; i++) {
        cout << cricketers[i] << " ";
    }
    cout << endl;

    return 0;
}
