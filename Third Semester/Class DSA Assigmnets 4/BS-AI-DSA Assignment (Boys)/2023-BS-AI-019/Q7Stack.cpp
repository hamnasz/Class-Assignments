// Implement a stack using an array and perform push and pop operations

#include <iostream>
using namespace std;
#define size 100  

// Function to Push elements in Stack Array
void push(int stack[], int &top, int value) 
{
    if (top > size) 
    {
        cout << "Stack is Full\n";
    } 
    else 
    {
        stack[++top] = value;
    }
}

// Function to Pop elements from Stack Array
void pop(int stack[], int &top) 
{
    if (top < 0) 
    {
        cout << "Already Empty\n";
    } 
    else 
    {
        top--;
    }
}

// Function to Display elements of Stack Array
void display(int stack[], int top)
{
    if (top < 0) 
    {
        cout << "Stack is Empty\n";
    } 
    else 
    {
        cout<<"Top Elemnet: "<< stack[top] << endl;
    }
}

int main() 
{
    int stack[size];
    int top = -1;
    
    for(int i=0; i<5; i++)
    {
        cin>>stack[++top];
    }

    cout << "\nTop element before pushing or popping! " << endl;
    display(stack, top);

    

    cout << "\nTop element after popping is! " << endl;
    pop(stack, top);
    display(stack, top);

    cout << "\nTop element after pushing is! " << endl;
    push(stack, top, 19);
    display(stack, top);
    return 0;
}
