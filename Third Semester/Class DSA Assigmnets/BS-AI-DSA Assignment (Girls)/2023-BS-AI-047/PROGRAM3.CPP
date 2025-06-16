#include <iostream>
#include <string>
using namespace std;

int main() {
    // Array of grocery items
    string groceryList[5] = {"Milk", "Eggs", "Bread", "Butter", "Apples"};
    
    cout << "Grocery List:" << endl;
    
    // Loop through the array and display each item
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << groceryList[i] << endl;
    }

    return 0;
}
