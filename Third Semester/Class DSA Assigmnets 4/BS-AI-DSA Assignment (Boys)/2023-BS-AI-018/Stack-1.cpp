#include <iostream>
using namespace std;

class Stack {
    int arr[5];
    int top;

public:
    Stack() : top(-1) {}

    void push(int x) {
        if (top >= 4) {
            cout << "Stack overflow" << endl;
        } else {
            arr[++top] = x;
        }
    }

    void pop() {
        if (top < 0) {
            cout << "Stack underflow" << endl;
        } else {
            top--;
        }
    }

    int peek() {
        if (top >= 0) return arr[top];
        return -1;
    }

    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.pop();
    cout << "Top element: " << s.peek() << endl;

    return 0;
}