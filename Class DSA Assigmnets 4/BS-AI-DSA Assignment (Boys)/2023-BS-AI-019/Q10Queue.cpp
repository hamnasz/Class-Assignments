// Check if the elements in a queue form a palindrome

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// Function to check if the elements in the queue form a palindrome
int palindrome(queue<int> q) 
{
    stack<int> s; 

    // Transfer elements from the queue to the stack
    for (int i = 0; i < q.size(); i++) 
    {
        s.push(q.front()); // Push the front element of the queue onto the stack
        q.push(q.front()); // Push the same element back into the queue
        q.pop(); // Remove the front element from the queue
    }

    // Check if the elements in the queue match the order in the stack
    for (int i = 0; i < q.size(); i++) 
    {
        // Compare the front of the queue with the top of the stack
        if (q.front() != s.top()) 
        {
            cout << "It is not a Palindrome!";
            return 2;
        }
        q.pop(); // Remove the front element from the queue
        s.pop(); // Remove the top element from the stack
    }

    cout << "It is a Palindrome!";
    return 1;
}

int main() 
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(1);

    palindrome(q);

    return 0;
}