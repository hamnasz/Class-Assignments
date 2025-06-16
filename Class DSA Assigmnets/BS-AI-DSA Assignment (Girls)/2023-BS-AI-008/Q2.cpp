#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 5, 40, 30};
    int min = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    cout << "The smallest number is: " << min << endl;
    return 0;
}

