#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

class Playlist
{
private:
    string songs[MAX_SIZE];
    int count;           

public:
    Playlist() : count(0) {} 


    void addBegin(const string &song)
    {
        if (count >= MAX_SIZE)
        {
            cout << "Playlist is full." << endl;
            return;
        }
        for (int i = count; i > 0; i--)
        {
            songs[i] = songs[i - 1];
        }
        songs[0] = song; 
        count++;     
    }

    void addEnd(const string &song)
    {
        if (count >= MAX_SIZE)
        {
            cout << "Playlist is full." << endl;
            return;
        }
        songs[count] = song;
        count++;            
    }

    void addPosition(int position, const string &song)
    {
        if (position < 0 || position > count || count >= MAX_SIZE)
        {
            cout << "Invalid position or playlist is full!" << endl;
            return;
        }
        for (int i = count; i > position; i--)
        {
            songs[i] = songs[i - 1]; 
        }
        songs[position] = song; 
        count++;                
    }

    void removeSong(const string &song)
    {
        for (int i = 0; i < count; i++)
        {
            if (songs[i] == song)
            {
                for (int j = i; j < count - 1; j++)
                {
                    songs[j] = songs[j + 1];
                }
                count--;
                cout << song << " has been removed from the playlist." << endl;
                return;
            }
        }
        cout << song << " not found in the playlist." << endl;
    }

    // Function to display the playlist
    void display() const
    {
        if (count == 0)
        {
            cout << "The playlist is empty." << endl;
            return;
        }
        cout << "Current Playlist: ";
        for (int i = 0; i < count; i++)
        {
            cout << songs[i] << " | ";
        }
        cout << endl;
    }
};

int main()
{
    Playlist playlist;
    string choice, song;
    int position;

    while (true)
    {
        cout << "\nEnter your choice (add_begin/add_end/add_position/remove/display/exit): ";
        cin >> choice;

        if (choice == "add_begin")
        {
            cout << "Enter song name to add at the beginning: ";
            cin >> song;
            playlist.addBegin(song);
        }
        else if (choice == "add_end")
        {
            cout << "Enter song name to add at the end: ";
            cin >> song;
            playlist.addEnd(song);
        }
        else if (choice == "add_position")
        {
            cout << "Enter position (0 for the beginning, etc.): ";
            cin >> position;
            cout << "Enter song name to add at position " << position << ": ";
            cin >> song;
            playlist.addPosition(position, song);
        }
        else if (choice == "remove")
        {
            cout << "Enter song name to remove: ";
            cin >> song;
            playlist.removeSong(song);
        }
        else if (choice == "display")
        {
            playlist.display();
        }
        else if (choice == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}