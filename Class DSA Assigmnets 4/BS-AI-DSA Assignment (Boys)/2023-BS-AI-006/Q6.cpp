#include<iostream>
using namespace std;

struct node
{
    int data;
    struct node *link;
};

struct node *n, *first, *last, *current, *temp;

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

void insertfirst(int data)
{
    n = new node();
    n->data = data;
    n->link = first;
    first = n;
}

void insertlast(int data)
{
    n = new node();
    n->data = data;
    n->link = NULL;
    last->link = n;
    last = n;
}

void insertmid(int value, int data)
{
    current = first;
    struct node *previous = NULL;

    n =new node();
    n->data = data;

    while (current != NULL)
    {
        if (current->data == value)
        {
            if (previous == NULL)
            {
                n->link = current;
                first = n;
            }
            else
            {
                previous->link = n;
                n->link = current;
            }
        }

        previous = current;
        current = current->link;
    }
}

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

    cout<<"\nDisplay after Insertion at First:\n";
    insertfirst(0);
    display();

    cout<<"\nDisplay after Insertion at Last:\n";
    insertlast(6);
    display();

    cout<<"\nDisplay after Insertion in Mid:\n";
    insertmid(5, 19);
    display();

    return 0;
}