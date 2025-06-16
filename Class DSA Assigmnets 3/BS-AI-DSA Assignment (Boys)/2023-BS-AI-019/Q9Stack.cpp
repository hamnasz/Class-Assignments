#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Function to evaluate a postfix expression
void postfixevaluation(string postfix)
{
    stack<int> stack;  // Stack to store operands during the evaluation process

    // Iterate through each character in the postfix expression
    for(int i = 0; i < postfix.length(); i++)
    {
        // If the character is a digit (0-9), convert it to an integer and push it onto the stack
        if(postfix[i] >= '0' && postfix[i] <= '9')
        {
            stack.push(postfix[i] - '0');  // Convert char to int by subtracting '0' (ASCII value)
        }
        else  // If the character is an operator
        {
            // Pop the top two operands from the stack
            int operand2 = stack.top();
            stack.pop();

            int operand1 = stack.top();
            stack.pop();

            // Perform the corresponding operation based on the operator
            switch(postfix[i])
            {
                case '+':
                    stack.push(operand1 + operand2);  // Addition
                    break;
                case '-':
                    stack.push(operand1 - operand2);  // Subtraction
                    break;
                case '*':
                    stack.push(operand1 * operand2);  // Multiplication
                    break;
                case '/':
                    stack.push(operand1 / operand2);  // Division
                    break;
            }
        }
    }

    // After processing the entire expression, the result will be the last remaining value in the stack
    cout << "Postfix Evaluation Result: " << stack.top() << endl;
}

int main()
{
    string postfix = "512=4*+3-";  // Example postfix expression
    postfixevaluation(postfix);  // Evaluate the postfix expression
    return 0;
}