#include <iostream>
using namespace std;
int main() {
    // Create an array of 5 fast food items
    string fastFood[5];
    fastFood[0] = "Burger";
    fastFood[1] = "Pizza";
    fastFood[2] = "Fries";
    fastFood[3] = "Tacos";
    fastFood[4] = "Hotdog";

    // Display the fast food list
    for (int i = 0; i < 5; i++) {
        cout << fastFood[i] << "\n";
    }
    return 0;
}
