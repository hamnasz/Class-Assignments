#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void reverseArray() {
    vector<int> array3 = {11, 22, 33, 44, 55, 66, 77, 88};
    reverse(array3.begin(), array3.end());

    cout << "Reversed Array: ";
    for (int num : array3) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    reverseArray();
    return 0;
}
