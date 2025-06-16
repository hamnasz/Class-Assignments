#include <iostream>

int main() {
    int values[5] = {1, 2, 3, 4, 5};
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += values[i];
    }

    cout << "Sum: " <<sum<<endl;

    return 0;
}
