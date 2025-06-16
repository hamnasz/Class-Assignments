#include<iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> num;

    cout<<"Enter 10 Numbers:"<<endl;
    for(int i=0; i<10; i++){
        int n;
        cin>>n;
        num.push_back(n);
    }

    int max = num[0];
    for(int i=0; i<num.size(); i++){
        if(max < num[i]){
            max = num[i];
        }
    }

    cout<<"Maximum Number: "<<max;
}