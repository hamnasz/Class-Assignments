#include <iostream>
#include <set>
using namespace std;

int main() {
    int arr[] = {1, 2, 2, 3, 4, 4, 5, 5, 6};
    set<int> unique;
    for (int i : arr) unique.insert(i);
    cout << "Array without duplicates: ";
    for (int i : unique) cout << i << " ";
    cout << endl;
    return 0;
}
