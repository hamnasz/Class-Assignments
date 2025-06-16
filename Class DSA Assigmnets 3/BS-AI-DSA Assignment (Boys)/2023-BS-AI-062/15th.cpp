#include <iostream>
#include <list>
#include <string>
using namespace std;
int main() {
    list<string> playlist;
    string choice, song;
    int position;
    while (true) {
        cout << "\nEnter your choice (add_begin/add_end/add_position/remove/display/exit): ";
        cin >> choice;
        if (choice == "add_begin") {
            cout << "Enter song name to add at the beginning: ";
            cin>>song;
            playlist.push_front(song);
        } 
        else if (choice == "add_end") {
            cout << "Enter song name to add at the end: ";
            cin>>song;
            playlist.push_back(song);
        } 
        else if (choice == "add_position") {
            cout << "Enter position (0 for the beginning, 1 for the first, etc.): ";
            cin >> position;
            cout << "Enter song name to add at position " << position << ": ";
            cin>>song;
            if (position < 0 || position > playlist.size()) {
                cout << "Invalid position!" << endl;
            } else {
                auto it = playlist.begin();
                advance(it, position); // Move iterator to the specified position
                playlist.insert(it, song);
            }
        } 
        else if (choice == "remove") {
            cout << "Enter song name to remove: ";
            cin>>song;
            playlist.remove(song);
        } 
        else if (choice == "display") {
            cout << "Current Playlist: ";
            for (const auto& s : playlist) {
                cout << s << " | ";
            }
            cout << endl;
        } 
        else if (choice == "exit") {
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}