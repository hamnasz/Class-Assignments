#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numbers = {5, 2, 8, 1, 3};
    int target = 8;

    auto iter = find(numbers.begin(), numbers.end(), target);

    if (iter != numbers.end()) {
        cout << "Target " << target << " found at index " << distance(numbers.begin(), iter) << endl;
    } else {
        cout << "Target " << target << " is not present in the vector" << endl;
    }

    return 0;
}
