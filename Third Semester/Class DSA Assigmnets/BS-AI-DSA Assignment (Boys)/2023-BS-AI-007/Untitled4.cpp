#include <iostream>
using namespace std;
int main()
{
    string books[] = {"1984\t\t\t= \tGeorge Orwell", "To Kill a Mockingbird\t= \tHarper Lee", "The Great Gatsby\t= \tF. Scott Fitzgerald", "Moby Dick\t\t= \tHerman Melville", "War and Peace\t\t= \tLeo Tolstoy"};
    cout << "Book Titles and Authors" << endl;
    cout << "-------------------------------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << books[i] << "\n";
    }
    return 0;
}
