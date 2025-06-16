#include <iostream>
#include <set>
using namespace std;

int main() {
    int array[7] = {4, 5, 2, 4, 3, 5, 1};
    set<int> unique_elements(array, array + 7);

    cout << "Array with unique elements: ";
    for (int el : unique_elements) {
        cout << el << " ";
    }
    cout << endl;
    return 0;
}
