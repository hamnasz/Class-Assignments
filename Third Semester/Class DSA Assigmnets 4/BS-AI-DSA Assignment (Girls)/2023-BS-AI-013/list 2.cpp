#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
    Node(int new_data)
    {
        data = new_data;
        next = nullptr;
    }
};
bool searchKey(Node* head, int key) {
    Node* curr = head;
    while (curr != NULL) {
        if (curr->data == key)
            return true;
        curr = curr->next;
    }
    return false;
}
int main() {
    Node* head = new Node(14);
    head->next = new Node(21);
    head->next->next = new Node(13);
    head->next->next->next = new Node(30);
    head->next->next->next->next = new Node(10);
      int key = 14;
    if (searchKey(head, key))
        cout << "Yes";
    else
        cout << "No";
    return 0;
}