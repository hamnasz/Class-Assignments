#include <iostream>
using namespace std;

class Stack {
private:
    int top;
    int arr[100];

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == 99);
    }

    void push(int val) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
        } else {
            arr[++top] = val;
        }
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
        } else {
            cout << "Popped element: " << arr[top--] << endl;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
        } else {
            for (int i = top; i >= 0; i--) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.display();

    s.pop();
    s.display();

    return 0;
}
