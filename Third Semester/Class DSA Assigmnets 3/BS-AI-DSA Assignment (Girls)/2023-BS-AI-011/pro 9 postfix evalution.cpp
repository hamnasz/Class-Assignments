//postfix evalution
#include <iostream>
using namespace std;
// Function to evaluate a postfix expression
int evaluatePostfix(const char* expression) {
    int stack[100];   // Stack array
    int front = -1;   // Initialize the front (top) of the stack
    // Iterate using a for loop until we hit the null terminator
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        // If the character is a digit, push it to the stack
        if (ch >= '0' && ch <= '9') {
            stack[++front] = ch - '0';  // Convert char to int and push
        }
        // If the character is an operator, pop two elements, apply the operator, and push the result
        else {
            int val1 = stack[front--];  // Pop the first operand
            int val2 = stack[front--];  // Pop the second operand

            switch (ch) {
                case '+':
                    stack[++front] = val2 + val1;  // Push result of addition
                    break;
                case '-':
                    stack[++front] = val2 - val1;  // Push result of subtraction
                    break;
                case '*':
                    stack[++front] = val2 * val1;  // Push result of multiplication
                    break;
                case '/':
                    stack[++front] = val2 / val1;  // Push result of division
                    break;
            }
        }
    }
    // The final result will be at the top (front) of the stack
    return stack[front];
}

int main() {
    char expression[100];
    cout << "Enter postfix expression: ";
    cin >> expression;

    cout << "Result of postfix evaluation: " << evaluatePostfix(expression) << endl;

    return 0;
}
