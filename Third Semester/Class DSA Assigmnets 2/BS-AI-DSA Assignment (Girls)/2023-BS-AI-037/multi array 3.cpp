#include <iostream>
using namespace std;

int main() {
    int arr[3][4] = {
        {3, 5, 7, 2},
        {8, -1, 4, 10},
        {12, 6, 9, 0}
    };
    int rows = 3;
    int cols = 4;

    
    int sum = 0;
    int total_elements = rows * cols;

  
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
    }

    
    double average = static_cast<double>(sum) / total_elements;

    cout << "The average value of the 2D array is: " << average << endl;

    return 0;
}