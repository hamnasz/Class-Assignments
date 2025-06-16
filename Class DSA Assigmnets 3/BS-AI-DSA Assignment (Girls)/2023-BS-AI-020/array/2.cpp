#include <iostream>
using namespace std;

int main() {
    int arr[5];
    
    cout << "Enter 5 integers:\n";
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }
    
    int max_value = arr[0];
    int min_value = arr[0];
    
    for (int i = 1; i < 5; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    
    cout << "Max: " << max_value << endl;
    cout << "Min: " << min_value << endl;

    return 0;
}
