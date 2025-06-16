#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int array[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    reverse(array, array + 8);

    cout << "Reversed Array: ";
    for (int i : array) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

