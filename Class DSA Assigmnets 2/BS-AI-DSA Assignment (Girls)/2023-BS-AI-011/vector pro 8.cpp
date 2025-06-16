//Find the Maximum Element in a Vector:
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {25, 18, 33, 45, 10};
    int maxElement = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > maxElement) {
            maxElement = vec[i];
        }
    }

    cout << "Maximum element in the vector: " << maxElement << endl;

    return 0;
}
