#include <iostream>
using namespace std;

int main() {
    int arr[] = {3, 5, 7, 2, 8, -1, 4, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    
    int min_val = arr[0];

   
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    cout << "The minimum value in the array is: " << min_val << endl;

    return 0;
}