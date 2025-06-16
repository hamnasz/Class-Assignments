#include <iostream>
using namespace std;

int main() {
    int arr[8] = {4,5, 7, 1,2 , 9, 3,6}; 
    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < 8; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    cout << "Maximum value: " << max << endl;
    cout << "Minimum value: " << min << endl;

    return 0;
}
