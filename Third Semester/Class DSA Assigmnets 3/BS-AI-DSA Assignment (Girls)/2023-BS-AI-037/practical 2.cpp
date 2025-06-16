#include <iostream>
using namespace std;

int main() {
    
    int numbers[5] = {3, 7, 1, 9, 4};
    
   
    int max = numbers[0];
    int min = numbers[0];

   
    for (int i = 1; i < 5; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }

  
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;
    cout << "Maximum value: " << max << endl;
    cout << "Minimum value: " << min << endl;

    return 0;
}
