#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec = {1, 2, 3, 4, 5};
    vec.erase(vec.begin() + 2);

    cout << "Vector after erase: ";
    for (int num : vec) {
        cout << num << " "<<endl;
    }
    return 0;
}