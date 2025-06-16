#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v = {10, 20, 10, 30, 20, 40};

    sort(v.begin(), v.end()); // Sort the vector

    v.erase(unique(v.begin(), v.end()), v.end()); // Remove duplicates

    cout << "Vector after removing duplicates: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}