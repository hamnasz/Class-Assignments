#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers;
    int n, element;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> element;
        numbers.push_back(element);
    }

    int maxElement = numbers[0]; 
    for (int i = 1; i < numbers.size(); i++) {
        if (numbers[i] > maxElement)
            maxElement = numbers[i];
    }

    cout << "Maximum element: " << maxElement << endl;

    return 0;
}
