#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> myList = {10, 20, 30, 40, 50};
    int target = 30;
    bool found = false;

    for (int value : myList) {
        if (value == target) {
            found = true;
            break;
        }
    }

    if (found)
        cout << "Element " << target << " found in the list." << endl;
    else
        cout << "Element " << target << " not found in the list." << endl;

    return 0;
}