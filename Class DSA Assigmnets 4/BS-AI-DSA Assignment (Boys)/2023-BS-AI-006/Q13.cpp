#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;

    cout << "Adding elements and displaying size and capacity:\n";
    for (int i = 0; i < 10; i++) {
        vec.push_back(i);
        
        cout << "After inserting " << i <<endl;
        cout << "Size: " << vec.size() <<endl;
        cout << "Capacity: " << vec.capacity() <<endl;
    }
    return 0;
}
