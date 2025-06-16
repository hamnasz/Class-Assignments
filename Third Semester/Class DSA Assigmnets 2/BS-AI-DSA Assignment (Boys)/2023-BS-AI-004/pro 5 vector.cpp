#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;

    // Adding elements to the vector
    vec.push_back(90);
    vec.push_back(20);
    vec.push_back(70);

    cout << "Vector after adding elements: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // Removing the last element
    vec.pop_back();

    cout << "Vector after removing the last element: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}
