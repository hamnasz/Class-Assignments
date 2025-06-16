#include <iostream>
using namespace std;

int main() {
    int array[10] = {3, 7, 2, 9, 4, 1, 5, 6, 8, 10};
    int sum = 0;

    for (int i = 0; i < 10; i++) {
        sum += array[i];
    }
    double average = static_cast<double>(sum) / 10;
    cout << "Sum: " << sum << ", Average: " << average << endl;
    return 0;
}
