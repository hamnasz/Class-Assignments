#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vec = {12, 45, 78, 45, 23, 45, 89, 90, 45, 56};
    int n = 45, count = 0;

    cout << "Search Number: " << n << endl;

    for (int i = 0; i < vec.size(); i++)
    {
        if (n == vec[i])
        {
            cout << "Found at Index: " << i << endl;
            count++;
        }
    }

    cout << "Total Occurrences: " << count << endl;
    return 0;
}