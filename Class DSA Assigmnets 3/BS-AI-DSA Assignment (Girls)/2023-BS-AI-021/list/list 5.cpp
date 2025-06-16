#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

void displayMenu() {
    cout << "\nMusic Playlist Manager Menu:" << endl;
    cout << "1. Add Song at Beginning" << endl;
    cout << "2. Add Song at End" << endl;
    cout << "3. Add Song at Specific Position" << endl;
    cout << "4. Remove Song" << endl;
    cout << "5. Display Playlist" << endl;
    cout << "6. Exit" << endl;
}

int main() {
    list<string> playlist;
    int choice = 0;
    string song;
    int position;

    do {
        displayMenu();
        cout << "Choose an option (1-6): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Enter song name to add at beginning: ";
                getline(cin, song);
                playlist.push_front(song);
                cout << "Song \"" << song << "\" has been added at the beginning." << endl;
                break;
            }

            case 2: {
                cout << "Enter song name to add at end: ";
                getline(cin, song);
                playlist.push_back(song);
                cout << "Song \"" << song << "\" has been added at the end." << endl;
                break;
            }

            case 3: {
                cout << "Enter song name to add: ";
                getline(cin, song);
                cout << "Enter position to add the song (starting from 1): ";
                cin >> position;
                cin.ignore();
                
                if (position < 1 || position > playlist.size() + 1) {
                    cout << "Invalid position!" << endl;
                } else {
                    auto it = playlist.begin();
                    advance(it, position - 1);
                    playlist.insert(it, song);
                    cout << "Song \"" << song << "\" has been added at position " << position << "." << endl;
                }
                break;
            }

            case 4: {
                cout << "Enter song name to remove: ";
                getline(cin, song);
                auto it = find(playlist.begin(), playlist.end(), song);
                if (it != playlist.end()) {
                    playlist.erase(it);
                    cout << "Song \"" << song << "\" has been removed." << endl;
                } else {
                    cout << "Song \"" << song << "\" not found in the playlist." << endl;
                }
                break;
            }

            case 5: {
                cout << "Current Playlist:" << endl;
                if (playlist.empty()) {
                    cout << "The playlist is empty." << endl;
                } else {
                    for (const auto& s : playlist) {
                        cout << "- " << s << endl;
                    }
                }
                break;
            }

            case 6: {
                cout << "Exiting the program." << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}