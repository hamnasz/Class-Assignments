#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {10, 50, 30, 40, 20};
    int maxVal = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > maxVal)
            maxVal = vec[i];
    }

    cout << "Maximum element in vector: " << maxVal << endl;
    return 0;
}
