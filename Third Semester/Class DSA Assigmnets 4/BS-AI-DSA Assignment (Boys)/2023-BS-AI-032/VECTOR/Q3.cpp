#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> numbers = {7, 2, 9, 3, 1, 5};
    sort(numbers.begin(), numbers.end());
    cout << "Sorted vector in ascending order: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
