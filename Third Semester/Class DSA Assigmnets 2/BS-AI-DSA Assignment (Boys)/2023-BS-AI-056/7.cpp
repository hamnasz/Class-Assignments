#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(2);
    vec.push_back(5);
    vec.push_back(2);
    
    int element = 2, count = 0;

    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == element) {
            count++;
        }
    }

    cout << "Number of times " << element << " appears: " << count << endl;
    return 0;
}

