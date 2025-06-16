// Removes duplicate values from a vector

#include <iostream>
#include <vector>
using namespace std;

void removeDuplicates(vector<int> &vec) 
{
    vector<int> unique;

    // Iterate over each number in the original vector
    for (int num : vec) 
    {
        int flag = 0; // Initialize a flag to track duplicates

        // Check if the number is already in the unique vector
        for (int uni : unique)
        {
            if (num == uni) // If the number matches an element in unique
            {
                flag++; // Increment the flag
                break;
            }
        }

        // If the flag is still 0, the number is unique
        if (flag == 0)
        {
            unique.push_back(num); // Add the unique number to the unique vector
        }
    }

    // Replace the original vector with the unique vector
    vec = unique;
}

int main() 
{
    vector<int> vec = {1, 2, 3, 2, 4, 5, 5, 6, 4, 7};

    // Print the original vector
    cout << "Original vector: ";
    for (int num : vec) 
    {
        cout << num << " ";
    }
    cout << endl;

    // Call the function to remove duplicates
    removeDuplicates(vec);

    // Print the vector after removing duplicates
    cout << "Vector after removing duplicates: ";
    for (int num : vec) 
    {
        cout << num << " ";
    }

    return 0;
}
