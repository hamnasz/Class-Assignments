#include <iostream> // For input and output operations
#define MAX_LINES 100 // Maximum number of lines in the document
#define MAX_LINE_LENGTH 100 // Maximum length of each line

using namespace std; // Use the standard namespace

// Global Variables
char document[MAX_LINES][MAX_LINE_LENGTH]; // 2D array to store the document lines
int numLines = 0; // Number of lines in the document
char clipboard[MAX_LINE_LENGTH]; // Clipboard to store a single line
char undoStack[MAX_LINES][MAX_LINE_LENGTH]; // Stack to store states for undo functionality
int undoTop = -1; // Top of the undo stack
char redoStack[MAX_LINES][MAX_LINE_LENGTH]; // Stack to store states for redo functionality
int redoTop = -1; // Top of the redo stack

// Function to copy one string to another
void copyString(char* dest, const char* src) { // dest is the target, src is the source
    int i = 0; // Index for iteration
    while (src[i] != '\0') { // Copy characters until null terminator
        dest[i] = src[i]; // Copy character
        i++; // Move to next character
    }
    dest[i] = '\0'; // Append null terminator
}

// Function to check if a substring exists within a string
char* findSubstring(char* str, const char* substr) { // str is the main string, substr is the pattern to find
    for (int i = 0; str[i] != '\0'; i++) { // Iterate through the main string
        int j = 0; // Index for substr
        while (substr[j] != '\0' && str[i + j] == substr[j]) { // Compare characters of substr
            j++; // Move to next character
        }
        if (substr[j] == '\0') { // If end of substr is reached
            return &str[i]; // Return pointer to the match
        }
    }
    return nullptr; // Return null if no match is found
}

// Function to calculate string length
int stringLength(const char* str) { // str is the input string
    int length = 0; // Initialize length counter
    while (str[length] != '\0') { // Iterate until null terminator
        length++; // Increment length
    }
    return length; // Return calculated length
}

// Function to push a state onto the undo stack
void pushUndoState() {
    if (numLines > 0) { // Check if there are lines in the document
        copyString(undoStack[++undoTop], document[numLines - 1]); // Copy last line to undo stack
    }
}

// Function to push a state onto the redo stack
void pushRedoState() {
    if (numLines > 0) { // Check if there are lines in the document
        copyString(redoStack[++redoTop], document[numLines - 1]); // Copy last line to redo stack
    }
}

// Function to undo the last action
void undo() {
    if (undoTop >= 0) { // Check if undo stack is not empty
        pushRedoState(); // Save current state to redo stack
        copyString(document[numLines - 1], undoStack[undoTop--]); // Restore last state from undo stack
        numLines--; // Decrease line count
    } else {
        cout << "Undo stack is empty!" << endl; // Notify user
    }
}

// Function to redo the last undone action
void redo() {
    if (redoTop >= 0) { // Check if redo stack is not empty
        pushUndoState(); // Save current state to undo stack
        copyString(document[numLines++], redoStack[redoTop--]); // Restore last state from redo stack
    } else {
        cout << "Redo stack is empty!" << endl; // Notify user
    }
}

// Function to add a line to the document
void addLine(const char* line) { // line is the input to add
    if (numLines < MAX_LINES) { // Check if there's space for more lines
        pushUndoState(); // Save current state to undo stack
        copyString(document[numLines++], line); // Add new line to the document
    } else {
        cout << "Document is full!" << endl; // Notify user
    }
}

// Function to delete the last line
void deleteLine() {
    if (numLines > 0) { // Check if there are lines to delete
        pushUndoState(); // Save current state to undo stack
        numLines--; // Reduce line count
    } else {
        cout << "No lines to delete!" << endl; // Notify user
    }
}

// Function to copy a line to the clipboard
void copyLine(int lineNumber) { // lineNumber is the index of the line to copy
    if (lineNumber >= 0 && lineNumber < numLines) { // Validate line number
        copyString(clipboard, document[lineNumber]); // Copy line to clipboard
        cout << "Copied: " << clipboard << endl; // Notify user
    } else {
        cout << "Invalid line number!" << endl; // Notify user
    }
}

// Function to paste the clipboard contents
void pasteLine() {
    if (numLines < MAX_LINES) { // Check if there's space for more lines
        pushUndoState(); // Save current state to undo stack
        copyString(document[numLines++], clipboard); // Paste clipboard content to document
    } else {
        cout << "Document is full!" << endl; // Notify user
    }
}

// Function to search for a word in the document
void searchWord(const char* word) { // word is the input to search
    bool found = false; // Flag to indicate if word is found
    for (int i = 0; i < numLines; i++) { // Iterate through lines
        if (findSubstring(document[i], word)) { // Check if word exists in line
            cout << "Found " << word << " in line " << i + 1 << ": " << document[i] << endl; // Notify user
            found = true; // Set flag to true
        }
    }
    if (!found) { // If word is not found
        cout << "Word not found!" << endl; // Notify user
    }
}

// Function to replace a word in the document
void replaceWord(const char* oldWord, const char* newWord) { // oldWord is to be replaced, newWord is the replacement
    for (int i = 0; i < numLines; i++) { // Iterate through lines
        char* pos = findSubstring(document[i], oldWord); // Find position of oldWord
        if (pos) { // If oldWord is found
            char temp[MAX_LINE_LENGTH]; // Temporary buffer for new line
            int oldWordLength = stringLength(oldWord); // Length of oldWord
            int newWordLength = stringLength(newWord); // Length of newWord
            int posIndex = pos - document[i]; // Calculate position index
            int k = 0; // Index for temp buffer

            for (int j = 0; j < posIndex; j++) { // Copy characters before oldWord
                temp[k++] = document[i][j];
            }

            for (int j = 0; j < newWordLength; j++) { // Copy newWord to temp buffer
                temp[k++] = newWord[j];
            }

            for (int j = posIndex + oldWordLength; document[i][j] != '\0'; j++) { // Copy characters after oldWord
                temp[k++] = document[i][j];
            }

            temp[k] = '\0'; // Append null terminator
            copyString(document[i], temp); // Update document line
        }
    }
    cout << "Replaced " << oldWord << " with " << newWord << "!" << endl; // Notify user
}

// Function to display the document
void displayDocument() {
    cout << "\nDocument:\n"; // Print header
    for (int i = 0; i < numLines; i++) { // Iterate through lines
        cout << i + 1 << ": " << document[i] << endl; // Print line number and content
    }
}

int main() {
    int choice; // To store user choice
    char buffer[MAX_LINE_LENGTH]; // Buffer for user input
    while (true) { // Infinite loop for menu
        cout << "\nAdvanced Text Editor\n"; // Display menu header
        cout << "1. Add Line\n2. Delete Line\n3. Copy Line\n4. Paste Line\n5. Search Word\n6. Replace Word\n7. Undo\n8. Redo\n9. Display Document\n10. Exit\n"; // Display menu options
        cout << "Enter your choice: "; // Prompt user for choice
        cin >> choice; // Read choice
        cin.ignore(); // Consume newline character

        switch (choice) { // Handle user choice
            case 1:
                cout << "Enter line to add: "; // Prompt for line input
                cin.getline(buffer, MAX_LINE_LENGTH); // Read line input
                addLine(buffer); // Add line to document
                break;
            case 2:
                deleteLine(); // Delete last line from document
                break;
            case 3:
                cout << "Enter line number to copy: "; // Prompt for line number to copy
                int lineNumber; // Variable to store line number
                cin >> lineNumber; // Read line number
                copyLine(lineNumber - 1); // Call copyLine (convert to 0-based index)
                break;
            case 4:
                pasteLine(); // Paste the line from clipboard
                break;
            case 5:
                cout << "Enter word to search: "; // Prompt for word to search
                cin >> buffer; // Read word
                searchWord(buffer); // Search word in the document
                break;
            case 6:
                char oldWord[MAX_LINE_LENGTH], newWord[MAX_LINE_LENGTH]; // Buffers for old and new words
                cout << "Enter word to replace: "; // Prompt for old word
                cin >> oldWord; // Read old word
                cout << "Enter replacement word: "; // Prompt for new word
                cin >> newWord; // Read new word
                replaceWord(oldWord, newWord); // Replace oldWord with newWord
                break;
            case 7:
                undo(); // Undo the last action
                break;
            case 8:
                redo(); // Redo the last undone action
                break;
            case 9:
                displayDocument(); // Display the document content
                break;
            case 10:
                cout << "Exiting editor. Goodbye!\n"; // Exit message
                return 0; // Exit the program
            default:
                cout << "Invalid choice. Please try again.\n"; // Handle invalid input
                break;
        }
    }
}
