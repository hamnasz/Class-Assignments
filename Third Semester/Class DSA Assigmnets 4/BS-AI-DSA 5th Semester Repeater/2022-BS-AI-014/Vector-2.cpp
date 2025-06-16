#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 2, 3, 4, 4, 5};
    sort(vec.begin(), vec.end());
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    cout << "Vector without duplicates: ";
    for (int val : vec) cout << val << " ";
    cout << endl;

    return 0;
}
