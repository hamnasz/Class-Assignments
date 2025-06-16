#include <iostream>
using namespace std;

int main() {
    int numbers[10];
    int total = 0;

    cout << "Please enter 10 integers: ";
    for (int i = 0; i < 10; i++) {
        cin >> numbers[i];
        total += numbers[i];
    }
    
    double avg = static_cast<double>(total) / 10;
    cout << "Total: " << total << ", Average: " << avg << endl;

    return 0;
}
