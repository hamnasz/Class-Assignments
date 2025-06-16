#include<iostream>
using namespace std;

struct node {
    int data;
    struct node *link;
};

struct node *n, *first, *last, *current, *temp;

void add(int data) {
    if(first == NULL) {
        n = new node();
        n->data = data;
        n->link = NULL;
        first = last = n;
    }
    else {
        n = new node();
        n->data = data;
        n->link = NULL;
        last->link = n;
        last = n;
    }

}

void remove(int value) {
    current = first;
    struct node *previous = NULL;

    while (current != NULL) {
        if (current->data == value)
        {
            if (previous == NULL) {
                first = first->link;
            }
            else {
                previous->link = current->link;
            }

            delete current;
        }

        previous = current;
        current = current->link;
    }
}

void display()
{
    current = first;
    while(current != NULL) {
        cout<<current->data<<endl;
        current = current->link;
    }
}

int main()
{
    for(int i=1; i<=5; i++) {
        add(i);
    }

    cout<<"Display after Adding:\n";
    display();

    cout<<"\nDisplay after Removing:\n";
    remove(4);
    display();

    return 0;
}