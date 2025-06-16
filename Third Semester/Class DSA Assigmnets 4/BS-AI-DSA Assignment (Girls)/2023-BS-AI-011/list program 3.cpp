//Create a program to insert an element at the beginning, middle, and end of a linked list.

#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> myList = {10, 20, 30};

    // Insert at the beginning
    myList.push_front(5);

    // Insert at the end
    myList.push_back(40);

    // Insert in the middle
    auto it = myList.begin();
    for (int i = 0; i < 2; ++i) {  // Move iterator to the third position manually
        ++it;
    }
    myList.insert(it, 25);

    // Display list
    cout << "List after insertions: ";
    for (int elem : myList) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
