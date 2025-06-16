#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 2, 9, 1, 5, 6};

    sort(vec.begin(), vec.end());

    cout << "Sorted vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
