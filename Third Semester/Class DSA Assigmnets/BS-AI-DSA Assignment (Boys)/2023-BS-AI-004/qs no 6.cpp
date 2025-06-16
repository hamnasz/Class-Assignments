#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;  
    int numbers[SIZE] = {34, 12, 67, 23, 78};  

    int maxNum = numbers[0];
    int minNum = numbers[0];

    for (int i = 1; i < SIZE; i++) {
        if (numbers[i] > maxNum) {
            maxNum = numbers[i];  
        }
        if (numbers[i] < minNum) {
            minNum = numbers[i];  
        }
    }

    cout << "Maximum number: " << maxNum << endl;
    cout << "Minimum number: " << minNum << endl;

    return 0;
}
