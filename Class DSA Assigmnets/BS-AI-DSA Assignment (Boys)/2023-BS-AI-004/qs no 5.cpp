#include <iostream>
using namespace std;

int main() {
    string fruits[3] = {"Apple", "Banana", "Cherry"};

    cout << "String Array: ";
    for (int i = 0; i < 3; i++) {
        cout << fruits[i] << " ";
    }
    cout << endl;

    return 0;
}