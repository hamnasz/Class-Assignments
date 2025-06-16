#include <iostream>
#include <string>

struct Song {
    std::string title;
    Song* next;
    Song* prev;
};

class Playlist {
private:
    Song* head = nullptr;
    Song* tail = nullptr;

public:
    // Add a song to the beginning of the playlist
    void addSongAtBeginning(const std::string& title) {
        Song* newSong = new Song{title, head, nullptr};
        if (!head) {
            head = tail = newSong;
        } else {
            head->prev = newSong;
            head = newSong;
        }
        std::cout << "Added at beginning: " << title << std::endl;
    }

    // Add a song to the end of the playlist
    void addSongAtEnd(const std::string& title) {
        Song* newSong = new Song{title, nullptr, tail};
        if (!tail) {
            head = tail = newSong;
        } else {
            tail->next = newSong;
            tail = newSong;
        }
        std::cout << "Added at end: " << title << std::endl;
    }

    // Add a song at a specific position (1-based index)
    void addSongAtPosition(const std::string& title, int position) {
        if (position <= 1) {
            addSongAtBeginning(title);
            return;
        }

        Song* current = head;
        int currentIndex = 1;

        while (current && currentIndex < position - 1) {
            current = current->next;
            currentIndex++;
        }

        if (!current) {
            addSongAtEnd(title);
        } else {
            Song* newSong = new Song{title, current->next, current};
            if (current->next) {
                current->next->prev = newSong;
            } else {
                tail = newSong;
            }
            current->next = newSong;
            std::cout << "Added at position " << position << ": " << title << std::endl;
        }
    }

    // Remove a song from the playlist
    void removeSong(const std::string& title) {
        Song* current = head;
        while (current && current->title != title) {
            current = current->next;
        }

        if (!current) {
            std::cout << "Song not found: " << title << std::endl;
            return;
        }

        if (current == head) {
            head = current->next;
        }
        if (current == tail) {
            tail = current->prev;
        }
        if (current->prev) {
            current->prev->next = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        }

        delete current;
        std::cout << "Removed: " << title << std::endl;
    }

    // Display the current playlist
    void displayPlaylist() const {
        if (!head) {
            std::cout << "The playlist is empty." << std::endl;
            return;
        }

        std::cout << "Playlist:" << std::endl;
        Song* current = head;
        while (current) {
            std::cout << "- " << current->title << std::endl;
            current = current->next;
        }
    }

    // Destructor to clean up memory
    ~Playlist() {
        while (head) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;
    std::string title;
    int position;

    do {
        std::cout << "\n1. Add song at beginning\n2. Add song at end\n3. Add song at specific position\n";
        std::cout << "4. Remove song\n5. Display playlist\n6. Exit\nChoose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                std::cout << "Enter song title to add at beginning: ";
                std::getline(std::cin, title);
                playlist.addSongAtBeginning(title);
                break;
            case 2:
                std::cout << "Enter song title to add at end: ";
                std::getline(std::cin, title);
                playlist.addSongAtEnd(title);
                break;
            case 3:
                std::cout << "Enter song title: ";
                std::getline(std::cin, title);
                std::cout << "Enter position: ";
                std::cin >> position;
                std::cin.ignore();
                playlist.addSongAtPosition(title, position);
                break;
            case 4:
                std::cout << "Enter song title to remove: ";
                std::getline(std::cin, title);
                playlist.removeSong(title);
                break;
            case 5:
                playlist.displayPlaylist();
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
