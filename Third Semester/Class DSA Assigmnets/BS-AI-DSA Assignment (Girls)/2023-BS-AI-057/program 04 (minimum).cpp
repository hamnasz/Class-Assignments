#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 25, 15, 5, 20};
    int min = arr[0];

    for(int i = 1; i < 5; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }

    cout << "Minimum value: " << min << endl;
    return 0;
}
