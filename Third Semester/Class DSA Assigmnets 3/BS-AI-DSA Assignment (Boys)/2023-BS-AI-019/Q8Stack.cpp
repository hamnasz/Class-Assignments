#include <iostream>
#include <stack>
#include <string>
using namespace std;

void visitPage(stack<string>& history, string& page) 
{
    history.push(page);
    cout << "Visited: " << page << "\n";
}

void goBack(stack<string>& history) 
{
    if (history.empty()) 
    {
        cout << "No previous pages in history.\n";
    } 
    else 
    {
        cout << "Going back from: " << history.top() << "\n";
        history.pop();

        if (!history.empty()) 
        {
            cout << "Now on: " << history.top() << "\n";
        } 
        else 
        {
            cout << "No pages in history.\n";
        }
    }
}

int main() 
{
    stack<string> history;
    int choice;
    string page;

    while (true) 
    {
        cout << "\nBrowser History Menu:\n";
        cout << "1. Visit new page\n";
        cout << "2. Go back\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter page URL: ";
                cin >> page;
                visitPage(history, page);
                break;

            case 2:
                goBack(history);
                break;

            case 3:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
