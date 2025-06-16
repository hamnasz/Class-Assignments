#include <iostream>
using namespace std;
void rotateArray(int arr[], int n) {
    int temp = arr[0];
    for (int i = 0; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = temp;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    rotateArray(arr, 5);

    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
