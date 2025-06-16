#include <iostream>
#include <vector>
using namespace std;

void remove(vector<int> &vec) {
    vector<int> unique;

    for (int num : vec) {
        int flag = 0;

        for(int uni : unique) {
            if(num == uni) {
                flag++;
                break;
            }
        }

        if(flag == 0) {
            unique.push_back(num);
        }
    }

    vec = unique;
}

int main() 
{
    vector<int> vec = {8, 7, 25, 25, 42, 7, 8, 42};

    cout << "Original vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    remove(vec);

    cout << "After removing duplicates: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
