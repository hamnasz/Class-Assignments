#include <iostream>
using namespace std;

int main() {
    int numbers[5] = {12, 7, 25, 3, 19};  
    int max = numbers[0]; 
    int min = numbers[0];  

    // Loop through the array to find the maximum and minimum
    for (int i = 1; i < 5; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

    
    cout << "Maximum value in the array: " << max << endl;
    cout << "Minimum value in the array: " << min << endl;

    return 0;
}
