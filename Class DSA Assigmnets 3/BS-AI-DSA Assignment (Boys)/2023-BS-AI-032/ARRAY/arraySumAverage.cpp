#include <iostream>
using namespace std;

int main() {
    int arr[10] = {12, 7, 15, 9, 20, 5, 13, 8, 11, 10};
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    double average = static_cast<double>(sum) / 10;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    return 0;
}
