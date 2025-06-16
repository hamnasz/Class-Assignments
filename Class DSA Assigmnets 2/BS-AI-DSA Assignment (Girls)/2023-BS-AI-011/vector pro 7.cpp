#include <iostream>
//Adding Elements to a Vector (Push Back):

#include <vector>
using namespace std;

int main() {
    vector<int> vec;

    // Adding elements using push_back
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Vector after adding elements: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}
