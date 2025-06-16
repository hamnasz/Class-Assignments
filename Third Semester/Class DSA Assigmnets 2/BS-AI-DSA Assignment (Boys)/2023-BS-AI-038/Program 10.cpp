#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> firstVector = {1, 2, 3};
    vector<int> secondVector = {4, 5, 6};
    vector<int> combinedVector;

    combinedVector.insert(combinedVector.end(), firstVector.begin(), firstVector.end());
    combinedVector.insert(combinedVector.end(), secondVector.begin(), secondVector.end());

    cout << "Combined vector: ";
    for (int i = 0; i < combinedVector.size(); i++) {
        cout << combinedVector[i] << " ";
    }
    cout << endl;

    return 0;
}
