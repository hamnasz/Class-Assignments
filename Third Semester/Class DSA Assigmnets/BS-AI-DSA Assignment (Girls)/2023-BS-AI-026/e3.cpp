#include <iostream>
using namespace std;

int main() {
    // Create an array of 5 games
    string games[5] = {"Football", "Basketball", "Tennis", "Cricket", "Volleyball"};

    // Display the games list
    cout << "List of Games:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << games[i] << endl;
    }

    return 0;
}
