#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {10, 20, 30, 40, 50};

    vec.pop_back(); // Remove the last element

    for (int i = 0; i < vec.size(); i++) {
        cout << "Element " << i << ": " << vec[i] << endl;
    }

    return 0;
}
