#include <iostream>
using namespace std;

int main() {
    int arr[10];
    int sum = 0;
    
    cout << "Enter 10 integers:\n";
    for (int i = 0; i < 10; i++) {
        cin >> arr[i];
        sum += arr[i];
    }
    
    double average = sum / 10.0; // Using 10.0 to ensure floating-point division
    
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
