#include <iostream>
#include <vector>
using namespace std;
int main() 
{
    vector<int> vec;
    
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Vector contents: ";
    for (int num : vec) {
        cout << num << " "<<endl;
    }
    vec.pop_back();

    cout << "After pop_back: ";
    for (int num : vec) {
       cout << num << " "<<endl;
    }
    return 0;
}