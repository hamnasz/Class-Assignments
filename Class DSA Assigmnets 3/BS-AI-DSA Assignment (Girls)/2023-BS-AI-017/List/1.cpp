#include <iostream>
#include <list>
using namespace std;

int main()
{
    list<string> shoppingList;
    string command, item;

    while (true)
    {
        cout << "Choose an action (add/remove/show/quit): ";
        cin >> command;

        if (command == "add")
        {
            cout << "Enter item to add: ";
            cin >> item;
            shoppingList.push_back(item);
        }
        else if (command == "remove")
        {
            cout << "Enter item to remove: ";
            cin >> item;
            shoppingList.remove(item);
        }
        else if (command == "show")
        {
            cout << "Your shopping list: ";
            for (const auto &it : shoppingList)
            {
                cout << it << " ";
            }
            cout << endl;
        }
        else if (command == "quit")
        {
            break; // Exit the loop
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}