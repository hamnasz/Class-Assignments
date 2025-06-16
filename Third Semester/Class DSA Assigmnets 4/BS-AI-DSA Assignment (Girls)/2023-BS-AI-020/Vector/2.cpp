#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 2, 3, 4, 4, 5};
    sort(vec.begin(), vec.end());
    auto it = unique(vec.begin(), vec.end());
    vec.resize(distance(vec.begin(), it));

    cout << "Vector after removing duplicates: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}