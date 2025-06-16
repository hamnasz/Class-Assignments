#include <iostream>
#include <stack>
#include <string>
using namespace std;

void displayText(stack<string>& Stack) 
{
    if (Stack.empty()) 
    {
        cout << "Text: (empty)\n";
    } 
    else 
    {
        cout << "Text: " << Stack.top() << "\n";
    }
}

int main() 
{
    stack<string> Stack;

    int choice;
    string inputText;

    while (true) 
    {
        cout << "\nText Editor Menu:\n";
        cout << "1. Add text\n";
        cout << "2. Undo last action\n";
        cout << "3. Display current text\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter text to add: ";
                cin.ignore();
                getline(cin, inputText);
                // Push the new state to the stack
                Stack.push(inputText);
                break;

            case 2:
                if (Stack.size() > 0) 
                {  // Ensure there is a previous state to revert to
                    Stack.pop();
                    cout << "Undo successful.\n";
                } 
                else 
                {
                    cout << "Nothing to undo.\n";
                }
                break;

            case 3:
                displayText(Stack);
                break;

            case 4:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
