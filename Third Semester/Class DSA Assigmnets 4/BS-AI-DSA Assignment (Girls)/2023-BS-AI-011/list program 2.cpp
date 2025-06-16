//- Write a program that searches for an element in a linked list.
#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> myList = {10, 20, 30, 40};

    int searchElement = 30;
    bool found = false;

    // Search for the element
    for (int elem : myList) {
        if (elem == searchElement) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << searchElement << " found in the list." << endl;
    } else {
        cout << searchElement << " not found in the list." << endl;
    }

    return 0;
}
