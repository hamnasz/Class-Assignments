#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

void removeDuplicates(vector<int>& vec) {
    unordered_set<int> seen;
    auto end = remove_if(vec.begin(), vec.end(), &seen {
        if (seen.find(value) != seen.end()) {
            return true;
        } else {
            seen.insert(value);
            return false;
        }
    });
    vec.erase(end, vec.end());
}

int main() {
    vector<int> vec = {1, 2, 2, 3, 4, 4, 5};
    removeDuplicates(vec);
    cout << "Vector after removing duplicates: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
