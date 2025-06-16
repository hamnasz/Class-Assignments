#include <iostream>
using namespace std;

int main() {
    // Create an array of 5 shopping items
    string shoppingList[5] = {"Handbag", "Shoes", "Dress", "Makeup Kit", "Accessories"};

    // Display the shopping list
    cout << "Shopping List:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << shoppingList[i] << endl;
    }

    return 0;
}
