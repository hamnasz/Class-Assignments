#include <iostream>
#include <list>
#include <string>
using namespace std;

    // Function to add item to the list
void addItem(list<string>& List, string& item) 
{
    List.push_back(item);
    cout << "Item \"" << item << "\" added to the list.\n";
}

// Function to remove an item from the list
void removeItem(list<string> List, string& item) 
{
    List.remove(item);
    cout << "Item \"" << item << "\" removed from the list.\n";
}

// Function to display the current list
void displayList(list<string> List) 
{
    if (List.empty()) 
    {
        cout << "The shopping list is empty.\n";
        return;
    }

    cout << "Current Shopping List:\n";
    for (string item : List) 
    {
        cout << "- " << item << "\n";
    }
}

int main() 
{
    list<string> List;
    int choice;
    string item;

    while (true) 
    {
        cout << "\nShopping List Menu:\n";
        cout << "1. Add item\n";
        cout << "2. Remove item\n";
        cout << "3. Display list\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter item to add: ";
                cin.ignore(); // Clear the newline character from the buffer
                getline(cin, item);
                addItem(List, item);
                break;
            case 2:
                cout << "Enter item to remove: ";
                cin.ignore(); // Clear the newline character from the buffer
                getline(cin, item);
                removeItem(List, item);
                break;

            case 3:
                displayList(List);
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
