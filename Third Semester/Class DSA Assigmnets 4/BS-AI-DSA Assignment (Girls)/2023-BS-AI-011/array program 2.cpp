//- Create a program that finds the maximum and minimum values in an array.
#include <iostream>
using namespace std;

int main() {
    int arr[] = {5, 3, 8, 1, 9, 4};
    int length = 6;  // Define the length manually

    int maxVal = arr[0];
    int minVal = arr[0];

    for (int i = 1; i < length; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }

    cout << "Maximum value: " << maxVal << endl;
    cout << "Minimum value: " << minVal << endl;
    return 0;
}
