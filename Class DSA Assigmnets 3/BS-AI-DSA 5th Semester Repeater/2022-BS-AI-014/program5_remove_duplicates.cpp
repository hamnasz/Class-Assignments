#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void removeDuplicates() {
    vector<int> array5 = {1, 2, 2, 3, 4, 4, 5};
    sort(array5.begin(), array5.end());
    array5.erase(unique(array5.begin(), array5.end()), array5.end());

    cout << "Unique Values: ";
    for (int num : array5) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    removeDuplicates();
    return 0;
}
