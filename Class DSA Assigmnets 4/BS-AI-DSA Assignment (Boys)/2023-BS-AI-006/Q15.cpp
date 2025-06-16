#include <iostream>
#include <vector>
using namespace std;

void assending(vector<int> &vec) {
    for(int i=0; i<vec.size(); i++) {
        for(int j = i+1; j<vec.size(); j++) {
            if(vec[j]<vec[i]) {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] =temp;
            }
        }
    }
}
int main() {
    vector<int> vec = {45, 78, 52, 14, 16, 23};

    cout << "Original vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    assending(vec);

    cout << "Sorted vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
