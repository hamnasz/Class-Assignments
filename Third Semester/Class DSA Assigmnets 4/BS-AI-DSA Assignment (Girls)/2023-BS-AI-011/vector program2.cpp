//- Implement a program that removes duplicate values from a vector.
#include <iostream>
#include <vector>

using namespace std;

void removeDuplicates(vector<int>& myVector) {
    int n = myVector.size();
    if (n <= 1) {
        return;
    }

    int j = 0;
    for (int i = 1; i < n; i++) {
        if (myVector[i] != myVector[j]) {
            j++;
            myVector[j] = myVector[i];
        }
    }

    myVector.resize(j + 1);
}

int main() {
    vector<int> myVector = {1, 2, 2, 3, 4, 3, 1};

    cout << "Original Vector: ";
    for (int num : myVector) {
        cout << num << " ";
    }
    cout << endl;

    removeDuplicates(myVector);

    cout << "Vector after removing duplicates: ";
    for (int num : myVector) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}