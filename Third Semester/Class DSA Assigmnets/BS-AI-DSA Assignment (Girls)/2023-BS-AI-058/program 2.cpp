
#include <iostream>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int sum = 0;

    // Loop to calculate sum of array elements
    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    cout << "Sum of all elements: " << sum << endl;

    return 0;
}



