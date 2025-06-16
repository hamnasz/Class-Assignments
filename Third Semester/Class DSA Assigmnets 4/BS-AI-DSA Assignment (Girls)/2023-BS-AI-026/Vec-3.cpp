#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    int n, value;

    cout << "Enter the number of elements in the vector: ";
    cin >> n;

    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        vec.push_back(value);
    }

    // Bubble sort algorithm
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = 0; j < vec.size() - 1 - i; j++) {
            if (vec[j] > vec[j + 1]) {
                // Swap elements
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }

    cout << "Sorted vector in ascending order: ";
    for (const int& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;

    return 0;
}
