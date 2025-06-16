// Sort a vector of integers in ascending order

#include <iostream>
#include <vector>
using namespace std;

void sort(vector<int> &vec) // Function to sort a vector of integers
{
    // Outer loop iterates through each element of the vector
    for (int i = 0; i < vec.size(); i++)
    {
        // Inner loop compares the current element with the elements that follow it
        for (int j = i + 1; j < vec.size(); j++)
        {
            // If the next element is smaller than the current element, swap them
            if (vec[j] < vec[i])
            {
                int temp = vec[i]; // Store the current element in a temporary variable
                vec[i] = vec[j]; // Assign the smaller element to the current position
                vec[j] = temp; // Assign the temporary variable (original current element) to the next position
            }
        }
    }
}

int main() 
{
    vector<int> vec = {34, 7, 23, 32, 5, 62};

    // Print the original vector
    cout << "Original vector: ";
    for (int num : vec) 
    {
        cout << num << " ";
    }
    cout << endl;

    // Call the sort function to sort the vector
    sort(vec);

    // Print the sorted vector
    cout << "Sorted vector in ascending order: ";
    for (int num : vec) 
    {
        cout << num << " ";
    }

    return 0;
}
