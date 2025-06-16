#include <iostream>
using namespace std;

int main() {
    int arr[5] = {1, 23, 45, 22, 19};
    
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << endl;
    }

    int largest = arr[0];
    for (int i = 1; i < 5; i++) {
        if (arr[i] > largest) {
            largest = arr[i];
        }
    }
    
    cout << "The largest number is          " << largest << endl;
    
    return 0;
}

