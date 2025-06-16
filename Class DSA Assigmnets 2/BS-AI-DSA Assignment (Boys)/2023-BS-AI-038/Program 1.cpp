#include <iostream>
using namespace std;

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    int largest = numbers[0];
    for (int i = 1; i < length; i++) {
        if (numbers[i] > largest) {
            largest = numbers[i];
        }
    }

    cout << "The largest element in the array is: " << largest << endl;
    return 0;
}
