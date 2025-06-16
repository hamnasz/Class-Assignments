#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);
    
    int element = 30, index = -1;

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == element) {
            index = i;
            break;
        }
    }

    if (index != -1)
        cout << "Index of " << element << ": " << index << endl;
    else
        cout << element << " not found in vector." << endl;

    return 0;
}

