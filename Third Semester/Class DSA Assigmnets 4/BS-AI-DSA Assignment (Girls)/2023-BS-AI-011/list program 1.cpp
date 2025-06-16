// Implement a program to add, remove, and display elements in a linked list

#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> myList;

    // Add elements
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    // Display elements
    cout << "List elements: ";
    for (int elem : myList) {
        cout << elem << " ";
    }
    cout << endl;

    // Remove an element (removes first occurrence of 20)
    myList.remove(20);

    cout << "List after removing 20: ";
    for (int elem : myList) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
