#include <iostream>
using namespace std;

int main() {
    int arr[10] = {5, 3, 8, 6, 2, 9, 1, 7, 4, 10};
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    double average = double(sum) / 10;
    cout << "Sum: " << sum << "\nAverage: " << average << endl;
    return 0;
}
