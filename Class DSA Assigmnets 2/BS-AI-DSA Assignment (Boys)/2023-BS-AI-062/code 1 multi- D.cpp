#include <iostream>
using namespace std;
int main() {
    int arr[3][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12}};

    int sum = 0;
    int totalElements = sizeof(arr) / sizeof(arr[0][0]); 
    for (const auto& row : arr) {
        for (int value : row) {
            sum += value;
        }
    }
    double average = static_cast<double>(sum) / totalElements; 
    cout << "Average: " << average <<endl; 
    return 0;
}
