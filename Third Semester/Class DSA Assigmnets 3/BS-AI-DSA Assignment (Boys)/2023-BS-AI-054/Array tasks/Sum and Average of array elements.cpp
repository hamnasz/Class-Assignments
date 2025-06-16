#include <iostream>
using namespace std;

int main() {
    int numbers[10] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};  
    double sum = 0;
    double average;

    // Calculate the sum of the array elements
    for (int i = 0; i < 10; i++) {
        sum += numbers[i];
    }

    // Calculate the average
    average = sum / 10;

   
    cout << "Sum of array elements: " << sum << endl;
    cout << "Average of array elements: " << average << endl;

    return 0;
}
