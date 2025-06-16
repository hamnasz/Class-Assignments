#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void maxAndMin() {
    vector<int> array2 = {15, 22, 8, 19, 31};
    int max_value = *max_element(array2.begin(), array2.end());
    int min_value = *min_element(array2.begin(), array2.end());

    cout << "Max Value: " << max_value << "\n";
    cout << "Min Value: " << min_value << "\n";
}

int main() {
    maxAndMin();
    return 0;
}
