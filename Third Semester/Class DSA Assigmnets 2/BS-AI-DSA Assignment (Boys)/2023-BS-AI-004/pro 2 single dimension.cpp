#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0, maxElement = arr[0], minElement = arr[0];
    double average;

    for (int i = 0; i < 5; i++) {
        sum += arr[i];
        if (arr[i] > maxElement) maxElement = arr[i];
        if (arr[i] < minElement) minElement = arr[i];
    }

    average = sum / 5.0;

    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Maximum element: " << maxElement << endl;
    cout << "Minimum element: " << minElement << endl;

    return 0;
}
