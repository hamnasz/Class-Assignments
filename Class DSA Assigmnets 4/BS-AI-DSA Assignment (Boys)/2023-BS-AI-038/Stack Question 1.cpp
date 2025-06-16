#include <iostream>
using namespace std;

class Stack {
private:
    int top;
    int capacity;
    int* arr;

public:
    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack overflow! Cannot push " << value << endl;
            return;
        }
        arr[++top] = value;
        cout << "Pushed " << value << " to stack" << endl;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack underflow! Cannot pop" << endl;
            return -1;
        }
        cout << "Popped " << arr[top] << " from stack" << endl;
        return arr[top--];
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    int peek() {
        if (!isEmpty())
            return arr[top];
        else {
            cout << "Stack is empty" << endl;
            return -1;
        }
    }
};

int main() {
    Stack s(5);

    s.push(10);
    s.push(20);
    s.push(30);

    s.pop();

    cout << "Top element is " << s.peek() << endl;

    s.pop();
    s.pop();
    s.pop();

    return 0;
}
