#include <iostream>
#include <list>
#include <string>
using namespace std;
void displayPlaylist(list<string> playlist) 
{
    if (playlist.empty()) 
    {
        cout << "The playlist is empty.\n";
    } 
    else 
    {
        cout << "Current Playlist:\n";
        int index = 1;
        for (string song : playlist) 
        {
            cout << song <<endl;
        }
    }
}

void addSongAtPosition(list<string>& playlist, string& song, int position) 
{
    if (position < 1 || position > playlist.size() + 1) 
    {
        cout << "Invalid position.\n";
        return;
    }

    int pos = 1;
    for(auto i=playlist.begin(); i !=playlist.end(); i++)
    {
        if(pos == position)
        {
            playlist.insert(i, song);
        }
        pos++;
    }
   
    cout << "Added \"" << song << "\" at position " << position << ".\n";
}

void removeSong(list<string>& playlist, int position) 
{
    if (position < 1 || position > playlist.size()) 
    {
        cout << "Invalid position.\n";
        return;
    }

    int pos = 1;
    for(auto i=playlist.begin(); i !=playlist.end(); i++)
    {
        if(pos == position)
        {
            playlist.erase(i);
        }
    }
}

int main() 
{
    list<string> playlist;
    int choice;
    string song;
    int position;

    while (true) 
    {
        cout << "\nPlaylist Manager Menu:\n";
        cout << "1. Add song at the beginning\n";
        cout << "2. Add song at the end\n";
        cout << "3. Add song at a specific position\n";
        cout << "4. Remove song by position\n";
        cout << "5. Display playlist\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                cout << "Enter song name: ";
                cin.ignore();
                getline(cin, song);
                playlist.push_front(song);
                cout << "Added \"" << song << "\" at the beginning.\n";
                break;

            case 2:
                cout << "Enter song name: ";
                cin.ignore();
                getline(cin, song);
                playlist.push_back(song);
                cout << "Added \"" << song << "\" at the end.\n";
                break;

            case 3:
                cout << "Enter song name: ";
                cin.ignore();
                getline(cin, song);
                cout << "Enter position to add the song (1 to " << playlist.size() << "): ";
                cin >> position;
                addSongAtPosition(playlist, song, position);
                break;
            case 4:
                cout << "Enter position to remove the song (1 to " << playlist.size() << "): ";
                cin >> position;
                removeSong(playlist, position);
                break;
            case 5:
                displayPlaylist(playlist);
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
