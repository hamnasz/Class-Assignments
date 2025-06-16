#include <iostream>
#include <list>
using namespace std;


int main() {
    list<int> myList;
    
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    for(int it : myList){
    	cout<<it<<" ";
	}
    myList.push_front(9);
    auto it = myList.begin();
    advance(it, myList.size() / 2);
    myList.insert(it, 11);
    cout<<endl<<"After Adding in Front: ";
    for(int it : myList){
    	cout<<it<<" ";
	}
   
}
