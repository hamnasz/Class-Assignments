#include <iostream>
using namespace std;

int main() {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;

    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }

    double average = (double)sum / 10;

    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
