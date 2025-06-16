#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> myList = {20, 30, 40};

    // Insert at beginning
    myList.push_front(10);

    // Insert at end
    myList.push_back(50);

    // Insert at middle
    auto it = myList.begin();
    advance(it, 2); // Move iterator to the third position
    myList.insert(it, 25);

    cout << "List elements after insertions: ";
    for (int value : myList) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}