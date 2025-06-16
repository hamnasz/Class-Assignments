#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> myList;

    // Adding elements
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    cout << "List elements after adding: ";
    for (int value : myList) {
        cout << value << " ";
    }

    // Removing an element
    myList.pop_front();

    cout << "\nList elements after removing front: ";
    for (int value : myList) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}