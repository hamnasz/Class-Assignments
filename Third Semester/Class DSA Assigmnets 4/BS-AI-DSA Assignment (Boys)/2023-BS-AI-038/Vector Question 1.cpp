#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    int element;

    cout << "Enter the number of elements to add: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Enter element to add: ";
        cin >> element;
        vec.push_back(element);

        cout << "Element added: " << element << "\n";
        cout << "Size of vector: " << vec.size() << "\n";
        cout << "Capacity of vector: " << vec.capacity() << "\n";
    }

    return 0;
}
