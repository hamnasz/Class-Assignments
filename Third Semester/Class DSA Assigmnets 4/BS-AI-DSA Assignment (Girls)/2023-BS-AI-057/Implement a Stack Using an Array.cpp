#include <iostream>
#define MAX 100
using namespace std;

class Stack {
    int arr[MAX];
    int top;

public:
    Stack() : top(-1) {}

    void push(int data) {
        if (top >= MAX - 1) {
            cout << "Stack overflow\n";
        } else {
            arr[++top] = data;
        }
    }

    void pop() {
        if (top < 0) {
            cout << "Stack underflow\n";
        } else {
            cout << "Popped: " << arr[top--] << endl;
        }
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
    stack.pop();
    stack.display();

    return 0;
}
