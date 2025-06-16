#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> vec = {9,8,2,6,4,5,3,1};
    sort(vec.begin(), vec.end());
    cout << "Sorted vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}