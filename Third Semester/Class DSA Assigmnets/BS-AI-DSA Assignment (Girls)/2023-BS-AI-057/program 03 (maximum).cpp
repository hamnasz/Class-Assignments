#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 25, 15, 5, 20};
    int max = arr[0];

    for(int i = 1; i < 5; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    cout << "Maximum value: " << max << endl;
    return 0;
}
