#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void removeDuplicates(vector<int>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

int main() {
    vector<int> vec = {1, 2, 2, 3, 4, 4, 5, 6, 6};
    cout << "Original vector: ";
    for (int i : vec) cout << i << " ";
    cout << endl;

    removeDuplicates(vec);
    cout << "Vector after removing duplicates: ";
    for (int i : vec) cout << i << " ";
    cout << endl;

    return 0;
}