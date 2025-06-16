#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 2, 8, 3, 1, 6, 4};
    cout << "Original vector: ";
    for (int i : vec) cout << i << " ";
    cout << endl;

    sort(vec.begin(), vec.end());
    cout << "Vector after sorting: ";
    for (int i : vec) cout << i << " ";
    cout << endl;

    return 0;
}