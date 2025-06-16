#include <iostream>
#include <string>
using namespace std;
const int Mitems = 10; 
string SList[Mitems]; 
int iCount = 0; 
void addItem(const string& item) {
    if (iCount < Mitems) {
        SList[iCount++] = item;
        cout << "Item \"" << item << "\" added to the shopping list.\n";
    } else {
        cout << "The shopping list is full.\n";
    }
}
void rItem(const string& item) {
    int found = false;
    for (int i = 0; i < iCount; ++i) {
        if (SList[i] == item) {
            found = true;
            // Shift items to the left to fill the gap
            for (int j = i; j < iCount - 1; ++j) {
                SList[j] = SList[j + 1];
            }
            --iCount;
            cout << "Item \"" << item << "\" removed from the shopping list.\n";
            break;
        }
    }
    if (!found) {
        cout << "Item \"" << item << "\" not found in the shopping list.\n";
    }
}
void displayList() {
    if (iCount == 0) {
        cout << "The shopping list is empty.\n";
    } else {
        cout << "Shopping List:\n";
        for (int i = 0; i < iCount; ++i) {
            cout << "- " << SList[i] << endl;
        }
    }
}

int main() {
    int option;
    string item;

    while (true) {
        cout << "\nOptions:\n";
        cout << "1.add item\n";
        cout << "2.remove item\n";
        cout << "3.display list\n";
        cout << "4.exit\n";
        cout << "Choose an option: ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                cout << "enter item to add: ";
                getline(cin, item);
                addItem(item);
                break;
            case 2:
                cout << "enter item to remove: ";
                getline(cin, item);
                rItem(item);
                break;
            case 3:
                displayList();
                break;
            case 4:
                cout << "exiting\n";
                return 0;
            default:
                cout << "invalid option\n";
                break;
        }
    }
}