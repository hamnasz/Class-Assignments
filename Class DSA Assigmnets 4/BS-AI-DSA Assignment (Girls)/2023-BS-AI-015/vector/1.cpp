#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> vec;
    for (int i = 1; i <= 4; i++) {
        vec.push_back(i);
        cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
    }
    return 0;
}