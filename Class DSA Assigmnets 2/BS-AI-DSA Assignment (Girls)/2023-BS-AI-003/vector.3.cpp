#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> vec;
    vec.push_back(5);
    vec.push_back(10);
    vec.push_back(15);
    cout << "Vector after adding elements: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    return 0;
}