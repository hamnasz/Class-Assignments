#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> vec = {2,7,8,1,5,4,9};
    sort(vec.begin(), vec.end());
    cout << "Sorted vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}