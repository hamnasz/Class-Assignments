#include <iostream>

using namespace std;

class Stack {
private:
    int* arr;        // Array to hold stack elements
    int top;         // Index of the top element
    int capacity;    // Maximum number of elements in the stack

public:
    // Constructor to initialize stack
    Stack(int size) {
        arr = new int[size];  // Create an array of given size
        capacity = size;
        top = -1;             // Stack is initially empty
    }

    // Push operation
    void push(int value) {
        if (top == capacity - 1) {
            cout << "Stack overflow! Cannot push " << value << "." << endl;
            return;
        }
        arr[++top] = value;  // Increment top and add the value
        cout << value << " pushed to stack." << endl;
    }

    // Pop operation
    int pop() {
        if (top == -1) {
            cout << "Stack underflow! Cannot pop from empty stack." << endl;
            return -1; // Return an invalid value
        }
        return arr[top--]; // Return the top value and decrement top
    }

    // Peek operation to see the top element
    int peek() const {
        if (top == -1) {
            cout << "Stack is empty. Cannot peek." << endl;
            return -1; // Return an invalid value
        }
        return arr[top]; // Return the top value without popping it
    }

    // Destructor to free memory
    ~Stack() {
        delete[] arr; // Free the allocated memory
    }
};

int main() {
    Stack stack(5); // Create a stack of capacity 5

    stack.push(10);
    stack.push(20);
    stack.push(30);
    
    cout << "Top element is: " << stack.peek() << endl;

    cout << stack.pop() << " popped from stack." << endl;
    cout << "Top element is: " << stack.peek() << endl;

    stack.push(40);
    stack.push(50);
    stack.push(60); // This should cause overflow

    // Pop all elements from the stack
    while (stack.peek() != -1) {
        cout << stack.pop() << " popped from stack." << endl;
    }

    return 0;
}
