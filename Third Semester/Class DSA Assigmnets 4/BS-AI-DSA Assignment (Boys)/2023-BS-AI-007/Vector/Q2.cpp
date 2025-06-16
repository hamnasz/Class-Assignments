#include <iostream>
#include <vector>
using namespace std;

void remDup(vector<int>& vec) {
    vector<int> result;
    for (int i = 0; i < vec.size(); i++) {
        bool isDuplicate = false;
        for (int j = 0; j < result.size(); j++) {
            if (vec[i] == result[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            result.push_back(vec[i]);
        }
    }
    vec = result;
}

int main() {
    vector<int> vec = {1, 2, 2, 3, 4, 4, 5};

    cout << "Original vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    remDup(vec);

    cout << "Vector after removing duplicates: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
