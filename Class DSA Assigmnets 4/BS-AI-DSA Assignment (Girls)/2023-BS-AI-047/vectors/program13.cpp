#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;

    // Adding elements to the vector and displaying size and capacity
    for (int i = 1; i <= 5; i++) {
        vec.push_back(i);
        cout << "Added " << i << ", Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
    }

    return 0;
}
