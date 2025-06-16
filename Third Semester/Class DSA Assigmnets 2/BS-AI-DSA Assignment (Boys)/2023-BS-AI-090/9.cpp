#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec1 = {1, 2, 3};
    vector<int> vec2 = {4, 5, 6};
    vector<int> mergedVec;

    mergedVec.insert(mergedVec.end(), vec1.begin(), vec1.end());
    mergedVec.insert(mergedVec.end(), vec2.begin(), vec2.end());

    cout << "Merged vector: ";
    for (int i = 0; i < mergedVec.size(); i++) {
        cout << mergedVec[i] << " ";
    }
    cout << endl;

    return 0;
}
