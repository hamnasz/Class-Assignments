#include <iostream>
#include <vector>
using namespace std;

void SizeAndCapacity(vector<int>& vec) {
    cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
}

int main() {
    vector<int> vec;

    vec.push_back(10);
    SizeAndCapacity(vec);

    vec.push_back(20);
    SizeAndCapacity(vec);

    vec.push_back(30);
    SizeAndCapacity(vec);

    vec.push_back(40);
    SizeAndCapacity(vec);

    vec.push_back(50);
    SizeAndCapacity(vec);

    return 0;
}
