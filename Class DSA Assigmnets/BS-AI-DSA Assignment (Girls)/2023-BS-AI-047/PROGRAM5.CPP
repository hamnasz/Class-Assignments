#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;
    double grades[SIZE] = {85.5, 90.0, 78.5, 92.0, 88.5};
    double sum = 0.0, average;
    
    // Using a for loop to calculate the sum of grades
    for(int i = 0; i < SIZE; i++) {
        sum += grades[i];
    }
    
    // Calculating the average
    average = sum / SIZE;
    
    cout << "Sum of grades: " << sum << endl;
    cout << "Average grade: " << average << endl;
    
    return 0;
}
