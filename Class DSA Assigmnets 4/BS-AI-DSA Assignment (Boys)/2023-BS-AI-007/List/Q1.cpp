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
    myList.pop_back();
    cout<<endl<<"After Popping: ";
    for(int it : myList){
    	cout<<it<<" ";
	}
   
}
