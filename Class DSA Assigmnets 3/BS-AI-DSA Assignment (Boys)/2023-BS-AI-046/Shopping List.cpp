#include <iostream>
#include <list>
using namespace std;

int main() {
    list<string> shopping_list;
    shopping_list.push_back("Milk");
    shopping_list.push_back("Bread");
    shopping_list.remove("Milk");

    cout << "Shopping List: ";
    for (const string& item : shopping_list) {
        cout << item << " ";
    }
    cout << endl;
    return 0;
}
