#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> removeDuplicates(vector<int>& vec) {
    sort(vec.begin(), vec.end());  // Sort the vector
    auto last = unique(vec.begin(), vec.end());  // Remove duplicates
    vec.erase(last, vec.end());  // Erase extra elements after unique

    return vec;
}

int main() {
    vector<int> vec = {1, 2, 2, 3, 4, 4, 5, 5};

    cout << "Original vector: ";
    for (int n : vec) cout << n << " ";
    cout << endl;

    removeDuplicates(vec);

    cout << "Vector after removing duplicates: ";
    for (int n : vec) cout << n << " ";
    cout << endl;

    return 0;
}
