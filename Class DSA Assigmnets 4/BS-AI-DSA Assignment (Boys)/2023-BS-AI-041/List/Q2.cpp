#include <iostream>
#include <list>
using namespace std;


int main() {
    list<int> myList;
    int searchele;
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    for(int it : myList){
    	cout<<it<<" ";
	}
	
	cout<<endl<<"Enter Element to search: ";
	cin>>searchele;
	
	bool flag = false;
	for(int it : myList){
    	if(searchele==it){
    		flag = true;
		}
	}
	if(flag==true){
		cout<<"Element Found!";
	}else{
		cout<<"Not Found!";
	}
}
