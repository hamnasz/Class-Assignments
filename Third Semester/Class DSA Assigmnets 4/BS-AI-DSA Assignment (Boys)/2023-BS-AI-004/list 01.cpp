#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> myList;

    // Adding elements
    myList.push_back(10);
    myList.push_back(20);
    myList.push_front(5);

    // Displaying elements
    cout << "List elements: ";
    for (int x : myList) {
        cout << x << " ";
    }
    cout << endl;

    // Removing elements
    myList.pop_back(); // Removes the last element
    myList.pop_front(); // Removes the first element
    myList.remove(20); // Removes all occurrences of 20

    cout << "List after removal: ";
    for (int x : myList) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}