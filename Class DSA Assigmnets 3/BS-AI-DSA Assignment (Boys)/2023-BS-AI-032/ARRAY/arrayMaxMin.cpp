#include <iostream>
using namespace std;

int main() {
    int arr[5] = {7, 3, 9, 1, 6};
    int max = arr[0];
    int min = arr[0];
    
    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    cout << "Maximum: " << max << endl;
    cout << "Minimum: " << min << endl;
    return 0;
}
