#include <iostream>
using namespace std;
int main()
 {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int max = arr[0];
    int min = arr[0];
    for (int i = 1; i < 11; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    cout << "max value: " << max << endl;
    cout << "min value: " << min << endl;
    return 0;
}
