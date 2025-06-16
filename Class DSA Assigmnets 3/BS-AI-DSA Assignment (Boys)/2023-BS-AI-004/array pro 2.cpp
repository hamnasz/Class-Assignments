#include <iostream>
using namespace std;

int main() {
    int arr[5] = {12, 3, 45, 23, 8};
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    cout << "Max: " << max << "\nMin: " << min << endl;
    return 0;
}
