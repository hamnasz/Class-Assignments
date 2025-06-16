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
    
    int sum = 0;

    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }

    double average = static_cast<double>(sum) / vec.size();
    cout << "Average of the vector elements: " << average << endl;

    return 0;
}

