#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    cout << "Initial size: " << vec.size() << ", capacity: " << vec.capacity() << endl;

    vec.push_back(10);
    cout << "After adding 10: size: " << vec.size() << ", capacity: " << vec.capacity() << endl;

    vec.push_back(20);
    cout << "After adding 20: size: " << vec.size() << ", capacity: " << vec.capacity() << endl;

    vec.push_back(30);
    cout << "After adding 30: size: " << vec.size() << ", capacity: " << vec.capacity() << endl;

    return 0;
}