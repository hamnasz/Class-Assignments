#include <iostream>
#include <list>
using namespace std;
int main() {
    list<int> linkedList = {10, 20, 30};
    linkedList.push_front(5);
    auto it = linkedList.begin();
    advance(it, 2);
    linkedList.insert(it, 15);
    linkedList.push_back(35);
    cout << "Linked List: ";
    for (int val : linkedList) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
