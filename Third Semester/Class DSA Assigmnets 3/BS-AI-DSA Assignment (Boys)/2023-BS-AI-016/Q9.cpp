#include <iostream>
#include <string>
#include <stack>
using namespace std;

void evaluation(string postfix)
{
    stack<int> stack;

    for(int i = 0; i < postfix.length(); i++)
    {
        if(postfix[i] >= '0' && postfix[i] <= '9')
        {
            stack.push(postfix[i] - '0');
        }
        else
        {
            int operand2 = stack.top();
            stack.pop();

            int operand1 = stack.top();
            stack.pop();

   
            switch(postfix[i])
            {
                case '+':
                    stack.push(operand1 + operand2);
                    break;
                case '-':
                    stack.push(operand1 - operand2); 
                    break;
                case '*':
                    stack.push(operand1 * operand2);
                    break;
                case '/':
                    stack.push(operand1 / operand2);
                    break;
            }
        }
    }

    cout << "Postfix Evaluation Result: " << stack.top() << endl;
}

int main()
{
    string postfix = "512+4*+3-";
    evaluation(postfix); 
    return 0;
}