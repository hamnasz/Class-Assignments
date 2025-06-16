#include <iostream>
#include <list>
using namespace std;
int main() {
    list<int> linkedList;
    linkedList.push_back(10);
    linkedList.push_back(20);
    linkedList.push_front(5);
    cout << "Linked List: ";
    for (int val : linkedList) {
        cout << val << " ";
    }
    cout << endl;
    linkedList.pop_front();
    linkedList.pop_back();
    cout << "Linked List after removal: ";
    for (int val : linkedList) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
