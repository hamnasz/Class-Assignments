#include <iostream>
using namespace std;
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int sum = 0;
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double average = static_cast<double>(sum) / n;
    cout << "Average: " << average << std::endl;
    return 0;
}
