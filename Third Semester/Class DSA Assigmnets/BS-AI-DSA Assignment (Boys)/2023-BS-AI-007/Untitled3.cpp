#include <iostream>
using namespace std;
int main()
{
    string cities[] = {"Karachi\t\t= \t8.4M", "lahore\t\t= \t4.1M", "ISB\t\t= \t2.7M", "Fsd\t\t= \t2.3M", "Multan\t\t= \t1.7M"};
    cout << "City Names and Populations" << endl;
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << cities[i] << "\n";
    }
    return 0;
}
