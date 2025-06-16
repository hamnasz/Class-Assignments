#include <iostream>

class Stack {
private:
    int top;
    int capacity;
    int* array;

public:
    Stack(int size) {
        capacity = size;
        array = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] array;
    }

    void push(int value) {
        if (top == capacity - 1) {
            std::cout << "Stack Overflow" << std::endl;
        } else {
            array[++top] = value;
        }
    }

    void pop() {
        if (top == -1) {
            std::cout << "Stack Underflow" << std::endl;
        } else {
            top--;
        }
    }

    void display() const {
        if (top == -1) {
            std::cout << "Stack is empty" << std::endl;
        } else {
            for (int i = top; i >= 0; i--) {
                std::cout << array[i] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Stack stack(5);

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.display(); // Output should be: 3 2 1

    stack.pop();
    stack.display(); // Output should be: 2 1

    return 0;
}
