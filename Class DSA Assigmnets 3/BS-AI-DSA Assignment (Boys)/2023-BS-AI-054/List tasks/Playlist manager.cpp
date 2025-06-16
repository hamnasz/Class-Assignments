#include <iostream>
#include <list>
#include <string>
#include <algorithm> // Include for std::find
using namespace std;

int main() {
    list<string> playlist;
    string command, song;
    int position;

    while (true) {
        cout << "\nCommands: add_front, add_end, add_pos, remove, display, exit\nEnter command: ";
        cin >> command;
        cin.ignore(); // Clear newline from buffer

        if (command == "add_front" || command == "add_end") {
            cout << "Enter song: ";
            getline(cin, song);
            (command == "add_front") ? playlist.push_front(song) : playlist.push_back(song);
            cout << song << " added.\n";
        } 
        else if (command == "add_pos") {
            cout << "Enter position (0 for front): ";
            cin >> position;
            cout << "Enter song: ";
            cin.ignore();
            getline(cin, song);
            if (position < 0 || position > playlist.size()) {
                cout << "Invalid position.\n";
            } else {
                auto it = playlist.begin();
                advance(it, position);
                playlist.insert(it, song);
                cout << song << " added at position " << position << ".\n";
            }
        } 
        else if (command == "remove") {
            cout << "Enter song: ";
            getline(cin, song);
            auto it = find(playlist.begin(), playlist.end(), song); // Correct usage of find
            if (it != playlist.end()) {
                playlist.erase(it);
                cout << song << " removed.\n";
            } else {
                cout << "Song not found.\n";
            }
        } 
        else if (command == "display") {
            if (playlist.empty()) {
                cout << "The playlist is empty.\n";
            } else {
                cout << "Current Playlist:\n";
                for (const auto& s : playlist) {
                    cout << "- " << s << "\n";
                }
            }
        } 
        else if (command == "exit") {
            cout << "Exiting...\n";
            break;
        } 
        else {
            cout << "Invalid command.\n";
        }
    }
    return 0;
}
