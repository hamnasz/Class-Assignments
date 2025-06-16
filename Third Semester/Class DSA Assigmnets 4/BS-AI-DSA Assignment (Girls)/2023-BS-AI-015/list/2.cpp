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
int element(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key)
            return true;
        current = current->next;
    }
    return false;
}
int main() {
    Node* head = new Node(3);
    head->next = new Node(2);
    head->next->next = new Node(1);
    head->next->next->next = new Node(30);
    head->next->next->next->next = new Node(15);
      int key = 14;
    if (element(head, key))
        cout << "Yes";
    else
        cout << "No";
}