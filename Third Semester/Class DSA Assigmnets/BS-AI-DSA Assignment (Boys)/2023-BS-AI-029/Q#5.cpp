#include <iostream>
using namespace std;

int main() {
    string cities[5] = {"Karachi", "Lahore", "Islamabad", "Peshawar", "Quetta"};

    cout << "Cities in Pakistan:\n";
    for (int i = 0; i < 5; i++) {
        cout << cities[i] << endl;
    }

    return 0;
}