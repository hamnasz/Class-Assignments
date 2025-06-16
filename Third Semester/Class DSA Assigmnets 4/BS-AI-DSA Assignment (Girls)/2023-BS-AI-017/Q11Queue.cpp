// Counts the total number of elements in a queue without modifying the queue's order

#include <iostream>
#include <queue>
using namespace std; // Use the standard namespace to avoid prefixing std::

// Function to count the number of elements in the queue
int count(queue<int> q) 
{
    int count = 0; // Initialize a counter to zero
    int size = q.size();
    
    for (int i = 0; i < size; ++i) 
    {
        int element = q.front(); // Get the front element of the queue
        q.pop(); // Remove the front element from the queue
        q.push(element); // Push the element back to the queue to maintain its order
        count++; // Increment the counter for each element processed
    }
    return count;
}

int main() 
{
    queue<int> q;
    q.push(10);  
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(50);

    cout << "Total Number of Elements: " << count(q);

    return 0;
}
