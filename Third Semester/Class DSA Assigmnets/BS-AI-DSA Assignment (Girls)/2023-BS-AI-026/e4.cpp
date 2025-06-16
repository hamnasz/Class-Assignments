#include <iostream>
using namespace std;
int main() {
    // Create an array of 5 cities
    string cities[5];
    cities[0] = "New York";
    cities[1] = "London";
    cities[2] = "Tokyo";
    cities[3] = "Paris";
    cities[4] = "Sydney";

    // Display the cities list
    for (int i = 0; i < 5; i++) {
        cout << cities[i] << "\n";
    }
    return 0;
}
