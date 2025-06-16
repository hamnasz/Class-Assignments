#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> numbers = {5, 3, 8, 1, 2, 7};

    cout << "Original vector: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    // Sort the vector in ascending order
    sort(numbers.begin(), numbers.end());

    cout << "Sorted vector in ascending order: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}
