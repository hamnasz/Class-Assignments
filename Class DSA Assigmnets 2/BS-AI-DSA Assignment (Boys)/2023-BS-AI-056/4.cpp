#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    vec.push_back(23);
    vec.push_back(1);
    vec.push_back(56);
    vec.push_back(3);
    vec.push_back(9);

    int total_sum = 0;

    
    for (int i = 0; i < vec.size(); i++) {
        total_sum += vec[i];
    }

    cout << "Sum of the vector: " << total_sum << endl;
    return 0;
}

