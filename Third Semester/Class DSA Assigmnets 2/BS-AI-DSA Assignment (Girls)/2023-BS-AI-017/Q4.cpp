#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec = {10, 20, 30, 40, 50};

    cout << "\nPrint in Stored Order: ";
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << ", ";
    }

    cout << "\nPrint in Reverse Order: ";
    for (int i = vec.size() - 1; i >= 0; i--)
    {
        cout << vec[i] << ", ";
    }

    return 0;
}