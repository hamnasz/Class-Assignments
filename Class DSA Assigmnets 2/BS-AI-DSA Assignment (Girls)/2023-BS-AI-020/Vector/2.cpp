#include<iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> vec;
    int n, temp;
    cout << "Enter number of elements: ";
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> temp;
        vec.push_back(temp);
    }
    for(int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    return 0;
}
