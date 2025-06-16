#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 3, 8, 1, 4};

    cout << "Original vector: ";
    for (int n : vec) cout << n << " ";
    cout << endl;

    sort(vec.begin(), vec.end());

    cout << "Sorted vector: ";
    for (int n : vec) cout << n << " ";
    cout << endl;

    return 0;
}
