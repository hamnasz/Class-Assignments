#include <iostream>
using namespace std;

class Stack {
private:
    int top;
    int maxSize;
    int* stackArray;

public:
    // Constructor to initialize the stack
    Stack(int size) {
        maxSize = size;
        stackArray = new int[maxSize];
        top = -1;
    }

    // Function to add an element to the stack
    void push(int value) {
        if (top < maxSize - 1) {
            stackArray[++top] = value;
        }
    }

    // Function to remove an element from the stack
    void pop() {
        if (top >= 0) {
            top--;
        }
    }

    // Function to display the elements in the stack
    void display() {
        if (top < 0) {
            cout << "Stack is empty." << endl;
        } else {
            cout << "Stack elements: ";
            for (int i = 0; i <= top; i++) {
                cout << stackArray[i] << " ";
            }
            cout << endl;
        }
    }

    // Destructor to free allocated memory
    ~Stack() {
        delete[] stackArray;
    }
};

int main() {
    Stack stack(5);  // Create a stack of size 5

    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.display(); // Display stack contents

    stack.pop(); // Pop the top element

    stack.push(40);
    stack.push(50);
    stack.push(60);
    stack.push(70);  // This push should trigger overflow

    stack.display(); // Display stack contents

    return 0;
}
