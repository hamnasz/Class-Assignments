#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> vec = {5, 2, 8, 1, 3};

    sort(vec.begin(), vec.end());

    for (int i = 0; i < vec.size(); i++) {
        cout << "Element " << i << ": " << vec[i] << endl;
    }

    return 0;
}
