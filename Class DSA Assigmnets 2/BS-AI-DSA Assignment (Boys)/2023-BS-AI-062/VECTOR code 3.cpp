#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec = {1, 2, 3};
    vec.resize(5, 0); 

    cout << "Resized vector: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout <<endl;
    return 0;
}