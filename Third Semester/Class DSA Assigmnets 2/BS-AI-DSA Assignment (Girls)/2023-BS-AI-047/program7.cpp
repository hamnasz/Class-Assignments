#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // Declare a vector of strings
    vector<string> names;

    // Adding elements to the vector
    names.push_back("farina");
    names.push_back("laiba");
    names.push_back("qandeel");
    names.push_back("maria");

    // Output the elements of the vector
    cout << "Names in the list:\n";
    for (const string& name : names) {
        cout << name << endl; // Print each name
    }

    // Remove a name from the list
    names.erase(names.begin() + 2); // Remove "Charlie"

    // Output the updated list
    cout << "\nUpdated names list after removal:\n";
    for (const string& name : names) {
        cout << name << endl; // Print each name again
    }

    return 0; // End of the program
}
