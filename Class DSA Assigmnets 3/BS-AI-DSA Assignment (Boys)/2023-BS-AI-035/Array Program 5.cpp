#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int inputArray[10];
    vector<int> distinctValues;

    cout << "Enter 10 integers: ";
    for (int i = 0; i < 10; i++) {
        cin >> inputArray[i];

        // Add unique values to distinctValues
        if (find(distinctValues.begin(), distinctValues.end(), inputArray[i]) == distinctValues.end()) {
            distinctValues.push_back(inputArray[i]);
        }
    }

    cout << "Array without duplicates: ";
    for (int value : distinctValues) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}
