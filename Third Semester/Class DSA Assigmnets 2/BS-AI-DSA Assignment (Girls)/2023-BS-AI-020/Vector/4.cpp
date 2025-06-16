#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> vec = {10, 23, 35, 21, 18};
    int max = vec[0];
    for(int i = 1; i < vec.size(); i++) {
        if(vec[i] > max)
            max = vec[i];
    }
    cout << "Maximum element: " << max;
    return 0;
}
