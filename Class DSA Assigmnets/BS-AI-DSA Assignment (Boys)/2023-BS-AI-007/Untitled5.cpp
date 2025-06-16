#include <iostream>
using namespace std;
int main()
{
    string products[] = {"Laptop\t\t= \t70000", "Smartphone\t= \t50000", "Tablet\t\t= \t30000", "Monitor\t\t= \t15000", "Keyboard\t= \t2000"};
    cout << "Product List with Prices" << endl;
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << products[i] << "\n";
    }
    return 0;
}