#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    return 0;
}
