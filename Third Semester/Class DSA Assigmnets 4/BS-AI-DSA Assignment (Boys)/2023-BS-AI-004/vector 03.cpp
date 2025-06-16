#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v = {30, 10, 20, 40, 5};

    sort(v.begin(), v.end()); // Sort the vector in ascending order

    cout << "Sorted vector: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}