#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;
    for(int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    cout << "Sum: " << sum;
    return 0;
}
