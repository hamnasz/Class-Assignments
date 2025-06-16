#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {5, 3, 1, 4, 2}; // Initialize the vector with unsorted elements

    std::sort(vec.begin(), vec.end()); // Sort the vector in ascending order

    // Display the sorted vector
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
