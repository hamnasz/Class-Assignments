#include <iostream>
using namespace std;

class Stack {
public:
    int arr[5];
    int top;

    Stack() : top(-1) {}

    void push(int value) {
        if (top == 4) {
            cout << "Stack overflow!" << endl;
            return;
        }
        arr[++top] = value;
    }

    void pop() {
        if (top == -1) {
            cout << "Stack underflow!" << endl;
            return;
        }
        top--;
    }

    void display() {
        for (int i = 0; i <= top; i++) {
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
    cout << "Stack after popping: ";
    stack.display();

    return 0;
}