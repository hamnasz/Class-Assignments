#include <iostream>
using namespace std;

int main() {
    int arr[6] = {10, 20, 30, 40, 5, 25};
    int max = arr[0];
    for (int i = 1; i < 6; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    cout << "Maximum element in the array: " << max << endl;
    return 0;
}
