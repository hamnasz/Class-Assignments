#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {10, 20, 5, 15, 30};
    int maxElement = vec[0], minElement = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > maxElement) maxElement = vec[i];
        if (vec[i] < minElement) minElement = vec[i];
    }

    cout << "Maximum element in vector: " << maxElement << endl;
    cout << "Minimum element in vector: " << minElement << endl;

    return 0;
}
