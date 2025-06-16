#include <iostream>
using namespace std;

int main() {
    int arr[] = {3, 5, 7, 2, 8, -1, 4, 10, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

   
    double average = static_cast<double>(sum) / n;

    cout << "The average value of the array is: " << average << endl;

    return 0;
}
