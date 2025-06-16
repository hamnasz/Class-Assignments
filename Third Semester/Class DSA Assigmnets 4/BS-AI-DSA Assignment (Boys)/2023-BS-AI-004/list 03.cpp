#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> myList = {10, 20, 30};

    // Inserting at the beginning
    myList.push_front(5);

    // Inserting at the end
    myList.push_back(40);

    // Inserting at the middle
    list<int>::iterator it = myList.begin();
    advance(it, 2); // Move the iterator to the third element
    myList.insert(it, 25);

    cout << "List after insertions: ";
    for (int x : myList) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}