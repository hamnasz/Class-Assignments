#include <iostream>
using namespace std;

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int total = 0;

    for (int i = 0; i < length; i++) {
        total += numbers[i];
    }

    cout << "The total sum of the array elements is: " << total << endl;
    return 0;
}
