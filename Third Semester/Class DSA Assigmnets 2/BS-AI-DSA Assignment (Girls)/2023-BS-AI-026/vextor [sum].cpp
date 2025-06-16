#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> numbers;
    int n, element, sum = 0;

    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> element;
        numbers.push_back(element);
    }

    for (int i = 0; i < numbers.size(); i++)
        sum += numbers[i];

    cout << "Sum of elements: " << sum << endl;

    return 0;
}
