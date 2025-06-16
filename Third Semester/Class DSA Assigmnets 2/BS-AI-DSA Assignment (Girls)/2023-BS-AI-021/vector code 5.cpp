#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec = {1, 2, 3, 5};
    vec.insert(vec.begin() + 3, 4);

    cout << "Vector after insertion: ";
    for (int num : vec) {
        cout << num << " "<<endl;
    }
    return 0;
}