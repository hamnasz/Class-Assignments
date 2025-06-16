#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 4, 5};

    vec.insert(vec.begin() + 2, 3); // Insert 3 at the third position

    for (int i = 0; i < vec.size(); i++) {
        cout << "Element " << i << ": " << vec[i] << endl;
    }

    return 0;
}
