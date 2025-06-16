#include <iostream>
using namespace std;

class Stack {
private:
    int* arr;         // Array to store stack elements
    int top;          // Index of the top element
    int maxSize;      // Maximum size of the stack

public:
    // Constructor to initialize the stack
    Stack(int size) {
        maxSize = size;
        arr = new int[maxSize];
        top = -1;  // Stack is initially empty
    }

    // Destructor to free memory
    ~Stack() {
        delete[] arr;
    }

    // Function to add an element to the stack (push)
    void push(int value) {
        if (top >= maxSize - 1) {
            cout << "Stack overflow! Cannot push " << value << "." << endl;
            return;
        }
        arr[++top] = value;
        cout << "Pushed " << value << " onto the stack." << endl;
    }

    // Function to remove and return the top element of the stack (pop)
    int pop() {
        if (top < 0) {
            cout << "Stack underflow! Cannot pop an element." << endl;
            return -1;  // Return an invalid value to indicate underflow
        }
        int poppedValue = arr[top--];
        cout << "Popped " << poppedValue << " from the stack." << endl;
        return poppedValue;
    }

    // Function to display the elements in the stack
    void display() {
        if (top < 0) {
            cout << "The stack is empty." << endl;
            return;
        }
        cout << "Stack elements: ";
        for (int i = 0; i <= top; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Create a stack of size 5
    Stack stack(5);

    // Perform push operations
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Display the stack elements
    stack.display();

    // Perform pop operations
    stack.pop();
    stack.pop();

    // Display the stack elements after popping
    stack.display();

    // Try to pop again from the stack
    stack.pop();
    stack.pop();  // This will trigger stack underflow

    // Perform more push operations
    stack.push(40);
    stack.push(50);
    stack.push(60);
    stack.push(70);  // This will trigger stack overflow

    // Display the final stack elements
    stack.display();

    return 0;
}