#include <iostream>
using namespace std;

class Stack {
private:
    int top;
    int arr[5]; // Array size of 5 for simplicity

public:
    Stack() {
        top = -1;
        for (int i = 0; i < 5; i++) {
            arr[i] = 0;
        }
    }

    // Push operation
    void push(int value) {
        if (top == 4) {
            cout << "Stack Overflow" << endl;
        } else {
            top++;
            arr[top] = value;
        }
    }

    // Pop operation
    int pop() {
        if (top == -1) {
            cout << "Stack Underflow" << endl;
            return 0;
        } else {
            int popValue = arr[top];
            arr[top] = 0;
            top--;
            return popValue;
        }
    }

    // Display stack elements
    void display() {
        for (int i = 4; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Stack after pushing elements: ";
    stack.display();

    stack.pop();
    cout << "Stack after popping one element: ";
    stack.display();

    return 0;
}
  
