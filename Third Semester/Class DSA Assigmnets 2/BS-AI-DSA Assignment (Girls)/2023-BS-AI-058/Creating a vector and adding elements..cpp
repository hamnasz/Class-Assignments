#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for (int i = 0; i < vec.size(); i++) {
        cout << "Element " << i << ": " << vec[i] << endl;
    }

    return 0;
}
