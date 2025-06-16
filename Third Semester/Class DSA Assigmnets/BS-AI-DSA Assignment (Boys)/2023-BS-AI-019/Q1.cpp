// Storing Subject Marks
#include <iostream>
#include <string>
using namespace std;
int main()
{
    // Declare and Initialize Arrays
    string subjects[5]={"DS", "AI", "Math", "English", "THQ"};
    int marks[5];

    // Take Subjects Marks as Input from User using Loop
    cout<<"Enter marks! "<<endl;
    for(int i=0; i<5; i++)
    {
        cout<<subjects[i]<<": ";
        cin>>marks[i];
    }

    // Display Subject with its Marks as Output using Loop
    cout<<"\nSubjects with marks: "<<endl;
    for(int i=0; i<5; i++)
    {
        cout<<subjects[i]<<": "<<marks[i]<<endl;
    }
    return 0;
}