#include <iostream>
#include <set>
using namespace std;

int main() {
    int array[] = {1, 2, 3, 4, 2, 5, 1, 6, 3};
    int size = sizeof(array) / sizeof(array[0]);
    set<int> uniqueValues;

    for (int i = 0; i < size; ++i) {
        uniqueValues.insert(array[i]);
    }

    cout << "Unique values: ";
    for (int value : uniqueValues) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}
