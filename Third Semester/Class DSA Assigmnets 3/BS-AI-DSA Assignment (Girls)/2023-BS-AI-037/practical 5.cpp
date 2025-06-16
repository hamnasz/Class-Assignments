#include <iostream>
#include <vector>
#include <unordered_set>

void removeDuplicates(const std::vector<int>& arr) {
    std::unordered_set<int> uniqueElements;
    std::vector<int> result;



    for (int num : arr) {
        if (uniqueElements.find(num) == uniqueElements.end()) {
            uniqueElements.insert(num);
            result.push_back(num);
        }
    }

   
    std::cout << "Array with unique values: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> array = {1, 2, 3, 2, 4, 3, 5, 6, 5, 7};
    removeDuplicates(array);
    return 0;
}