#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
class LinkedList {
private:
    Node* head;
public:
    LinkedList() {head=nullptr; }
    void add(int value) {
        Node* newNode=new Node();
        newNode->data=value;
        newNode->next=nullptr;
        if (head==nullptr) {
            head=newNode;
        } else {
            Node* temp=head;
            while (temp->next!= nullptr) {
                temp=temp->next;
            }
            temp->next=newNode;
        }
    }
    void remove(int value) {
        if (head==nullptr)
		 return;
        if (head->data==value) {
            Node* temp=head;
            head=head->next;
            delete temp;
            return;
        }
        Node* prev=head;
        Node* current=head->next;
        while(current!=nullptr) {
            if(current->data==value) {
                prev->next=current->next;
                delete current;
                return;
            }
            prev=current;
            current=current->next;
        }
    }
    void display() {
        Node*temp=head;
        while(temp!=nullptr) {
            cout<<temp->data<< " ";
            temp=temp->next;
        }
        cout<<endl;
    }
};
int main() {
    LinkedList list;    list.add(30);
    list.add(60);
    list.add(80);
    list.add(10);
    list.add(40);
    cout<<"list: ";
    list.display();
    list.remove(30);
    cout<<"new list: ";
    list.display();
}