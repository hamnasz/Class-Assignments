#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> v = {50, 10, 40, 20, 30};
    sort(v.begin(), v.end());

    cout << "Sorted vector: ";
    for (int num : v) cout << num << " ";
    cout << endl;

    return 0;
}
