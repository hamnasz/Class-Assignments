// Sum of All Elements in a 2D Array

#include <iostream>
using namespace std;

int main() {
    int arr[2][2] = {{40, 90}, {30, 40}};
    int sum = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            sum += arr[i][j]; // Calculate sum of all elements
        }
    }

    cout << "Sum of elements in 2D array: " << sum << endl;
    return 0;
}
