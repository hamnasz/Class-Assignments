#include <iostream>
#include <list>
using namespace std;
bool search(list<int>& linkedList, int value) {
    for (int val : linkedList) {
        if (val == value) return true;
    }
    return false;
}
int main() {
    list<int> linkedList = {10, 20, 30, 40};
    int searchValue = 20;
    if (search(linkedList, searchValue)) {
        cout << searchValue << " is in the list." << endl;
    } else {
        cout << searchValue << " is not in the list." << endl;
    }
    return 0;
}
