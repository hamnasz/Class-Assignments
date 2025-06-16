#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
        cout << "After inserting " << i << ": ";
        cout << "Size = " << vec.size() << ", Capacity = " << vec.capacity() << endl;
    }
    return 0;
}
