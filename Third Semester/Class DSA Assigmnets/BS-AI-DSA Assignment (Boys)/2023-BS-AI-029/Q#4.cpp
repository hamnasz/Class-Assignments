#include <iostream>
using namespace std;

struct City {
    string name;
    string province;
};

int main() {
    City cities[3] = {
        {"Karachi", "Sindh"},
        {"Lahore", "Punjab"},
        {"Peshawar", "Khyber Pakhtunkhwa"}
    };

    cout << "Cities in Pakistan:\n";
    for (int i = 0; i < 3; i++) {
        cout << cities[i].name << " - " << cities[i].province << endl;
    }

    return 0;
}