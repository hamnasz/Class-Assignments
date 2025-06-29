// Searches for an element in a linked list

#include<iostream>
using namespace std;

// Define Struct
struct node
{
    int data;
    struct node *link;
};

struct node *n, *first, *last, *current, *temp;

// Function to Add elements in Linked List
void create(int data)
{
    if(first == NULL)
    {
        n = new node();
        n->data = data;
        n->link = NULL;
        first = last = n;
    }
    else
    {
        n = new node();
        n->data = data;
        n->link = NULL;
        last->link = n;
        last = n;
    }

}

// Function to Search elements from Linked List
int search(int value)
{
    current = first;

    while (current != NULL)
    {
        if (current->data == value)
        {
            cout<<"Value Found!";
            return 2;
        }
        current = current->link;
    }
    cout<<"Value not Found!";
    return 1;
}

// Function to Display elements of Linked List
void display()
{
    current = first;
    while(current != NULL)
    {
        cout<<current->data<<endl;
        current = current->link;
    }
}

int main()
{
    for(int i=1; i<=5; i++)
    {
        create(i);
    }

    cout<<"Display after Creation:\n";
    display();

    int x;
    cout<<"Enter Value to Search: ";
    cin>>x;

    search(x);


    return 0;
}