#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> number;
    int element;
    for (int i = 0; i < 5; ++i) {
        cout << "Enter an element to add to the vector: ";
        cin >> element;
        number.push_back(element);
        cout << "Size after insertion: " << number.size() << endl;
        cout << "Capacity after insertion: " << number.capacity() << endl;
    }
    return 0;
}
