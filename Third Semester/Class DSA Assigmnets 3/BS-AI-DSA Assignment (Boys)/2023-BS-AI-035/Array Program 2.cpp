#include <iostream>
using namespace std;

int main() {
    int values[5];
    cout << "Please enter 5 integers: ";
    
    for (int i = 0; i < 5; i++) {
        cin >> values[i];
    }

    int maximum = values[0];
    int minimum = values[0];

    for (int i = 1; i < 5; i++) {
        if (values[i] > maximum) maximum = values[i];
        if (values[i] < minimum) minimum = values[i];
    }

    cout << "Maximum: " << maximum << ", Minimum: " << minimum << endl;

    return 0;
}
