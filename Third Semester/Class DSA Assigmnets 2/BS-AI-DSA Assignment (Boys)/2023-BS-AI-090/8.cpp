#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 2, 8, 1, 3};
    int element = 8;

    auto it = find(vec.begin(), vec.end(), element);

    if (it != vec.end()) {
        cout << "Element " << element << " found at position " << distance(vec.begin(), it) << endl;
    } else {
        cout << "Element " << element << " not found in the vector" << endl;
    }

    return 0;
}
