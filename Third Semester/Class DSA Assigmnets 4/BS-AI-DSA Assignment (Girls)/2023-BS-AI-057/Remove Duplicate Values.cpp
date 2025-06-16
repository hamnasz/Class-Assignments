#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void removeDuplicates(vector<int>& v) {
    unordered_set<int> seen;
    auto it = v.begin();
    while (it != v.end()) {
        if (seen.find(*it) != seen.end()) it = v.erase(it);
        else {
            seen.insert(*it);
            ++it;
        }
    }
}

int main() {
    vector<int> v = {10, 20, 10, 30, 20, 40};
    removeDuplicates(v);

    cout << "Vector without duplicates: ";
    for (int num : v) cout << num << " ";
    cout << endl;

    return 0;
}
