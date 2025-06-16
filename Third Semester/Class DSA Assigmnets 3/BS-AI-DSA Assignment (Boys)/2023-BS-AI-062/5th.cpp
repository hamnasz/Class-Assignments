#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 3, 6, 7, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    unordered_set<int> uniqueElements;
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (uniqueElements.find(arr[i]) == uniqueElements.end()) {
            uniqueElements.insert(arr[i]);
            result.push_back(arr[i]);
        }
    }

    cout << "Unique values: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
