#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    cout << "Reversed vector: ";
    for (int i = vec.size() - 1; i >= 0; i--) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}

