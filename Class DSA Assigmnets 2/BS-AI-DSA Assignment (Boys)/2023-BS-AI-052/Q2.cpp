#include <iostream>
#include <vector>
using namespace std;
int main(){
    int size=0;
    vector<int> num= {1, 2, 3, 4, 5};

    cout<<"Size of Each Element: "<<endl;
    for(int i=0; i<num.size(); i++){
        cout<<sizeof(num[i])<<endl;
        size += sizeof(num[i]);
    }

    cout<<"Vector Size: " <<num.size()<<endl;
    cout<<"Vector Memory Size: "<<size;
    return 0;
}