#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 3, 9, 1, 6};
    sort(vec.begin(), vec.end());
    cout << "Sorted vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
