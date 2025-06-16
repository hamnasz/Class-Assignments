#include <iostream>
using namespace std;

int main() {
    int laiba[] = {10, 25, 3, 50, 7};  // Initialize an array
    int size = sizeof(laiba) / sizeof(laiba[0]);
    
    int maxVal = laiba[0];
    int minVal = laiba[0];

    for (int i = 1; i < size; i++) {
        if (laiba[i] > maxVal) {
            maxVal = laiba[i];
        }
        if (laiba[i] < minVal) {
            minVal = laiba[i];
        }
    }

    cout << "Maximum value: " << maxVal << endl;
    cout << "Minimum value: " << minVal << endl;

    return 0;
}
