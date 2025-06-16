#include <iostream>
#include <string>
using namespace std;
int main() {
    string groceryItems[5] = {"Rice", "Sugar", "Flour", "Tea", "Oil"};
    double prices[5] = {300, 450, 500, 350, 400};
    double total = 0;
    cout << "\nYour Bill:\n";
    cout << "---------------------------------\n";
    for (int i = 0; i < 5; i++) {
        cout << groceryItems[i] << ": PKR " << prices[i] << endl;
        total += prices[i];
    }
    cout << "---------------------------------\n";
    cout << "Total Bill: PKR " << total << endl;
    return 0;
}