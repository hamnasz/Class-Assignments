#include <iostream>
using namespace std;

int main() {
    string fruits[3] = {"Apple", "Banana", "Cherry"};

    cout << "Fruits in the array:\n";
    for (int i = 0; i < 3; i++) {
        cout << fruits[i] << endl;
    }

    return 0;
}