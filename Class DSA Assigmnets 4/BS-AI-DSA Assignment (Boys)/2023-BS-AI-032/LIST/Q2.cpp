#include <iostream>
using namespace std;

class Node 
{ 
	public:
	int key; 
	Node* next; 
}; 

void push(Node** head_ref, int new_key) 
{ 
	Node* new_node = new Node();
	new_node->key = new_key; 
	new_node->next = (*head_ref); 
	(*head_ref) = new_node; 
}  

bool search(Node* head, int x) 
{ 
	Node* current = head; 
	while (current != NULL) 
	{ 
		if (current->key == x) 
			return true; 
		current = current->next; 
	} 
	return false; 
} 

int main() 
{
	Node* head = NULL; 
	int n, value, x;

	cout << "Enter the number of elements to add to the linked list: ";
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cout << "Enter value " << i + 1 << ": ";
		cin >> value;
		push(&head, value);
	}

	cout << "Enter the value to search for: ";
	cin >> x;

	if (search(head, x)) 
		cout << "Element Found";
	else 
		cout << "Not found";
	return 0; 
}
