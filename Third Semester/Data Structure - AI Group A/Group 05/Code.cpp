#include <iostream>
using namespace std;

const int N = 4; // Dimension of the puzzle grid (4x4)

// Structure to represent a move in the puzzle
struct Move {
    int x, y;     // Current position of the empty tile
    int dx, dy;   // Direction of the move (change in x and y)
    Move* next;   // Pointer to the next move in the stack
};

// Global pointer to the top of the stack for storing moves
Move* stackTop = nullptr;

// Push a new move onto the stack
void push(Move*& top, int x, int y, int dx, int dy) {
    Move* newMove = new Move{x, y, dx, dy, top}; // Create a new move //This links the new move to the existing stack (maintaining the linked list structure).
    top = newMove;                               // Update the stack top
}

// Check if the stack is empty
bool isEmpty(Move* top) {
    return top == nullptr;
}

// Pop the top move from the stack and return it
Move pop(Move*& top) {
    if (isEmpty(top)) {
        throw runtime_error("Stack is empty"); // Throw an error if the stack is empty
    }
    Move move = *top;         // Store the top move
    Move* temp = top;         // Temporarily store the top pointer
    top = top->next;          // Move the stack top to the next element
    delete temp;              // Free memory of the popped move
    return move;              // Return the popped move
}

// Clear the stack and free all memory
void clearStack(Move*& top) {  //reference to a pointer
    while (!isEmpty(top)) {
        pop(top); // Pop all elements from the stack
    }
}

// Print the current state of the puzzle
void printPuzzle(int puzzle[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (puzzle[i][j] == 0) // Empty tile
                cout << "    ";   // Print empty space for 0
            else
                cout << puzzle[i][j] << " "; // Print the tile value
        }
        cout << endl; // Newline for the next row
    }
    cout << endl;
}

// Check if the puzzle is solved by comparing it to the goal state
bool isSolved(int puzzle[N][N], int goal[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (puzzle[i][j] != goal[i][j]) // Check each tile
                return false;              // Return false if any tile doesn't match
        }
    }
    return true; // Return true if all tiles match
}

// Check if a move is valid (within the grid boundaries)
bool isValidMove(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// Swap the values of two variables
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Main function to play the puzzle game
void playGame(int start[N][N], int goal[N][N]) {
    int puzzle[N][N]; // Current state of the puzzle
    int emptyX, emptyY; // Position of the empty tile

    // Copy the start state to the puzzle and locate the empty tile
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            puzzle[i][j] = start[i][j];
            if (puzzle[i][j] == 0) { // Found the empty tile
                emptyX = i;
                emptyY = j;
            }
        }
    }

    while (true) {
        printPuzzle(puzzle); // Display the current puzzle state

        if (isSolved(puzzle, goal)) { // Check if the puzzle is solved
            cout << "Congratulations! You solved the puzzle!" << endl;
            break;
        }

        // Prompt the user for a move
        cout << "Enter move direction (w/a/s/d for up/left/down/right, u to undo): ";
        char move;
        cin >> move;

        int dx = 0, dy = 0; // Direction of movement
        if (move == 'w') dx = -1; // Move up
        else if (move == 's') dx = 1; // Move down
        else if (move == 'a') dy = -1; // Move left
        else if (move == 'd') dy = 1; // Move right
        else if (move == 'u') { // Undo the last move
            if (!isEmpty(stackTop)) {
                Move lastMove = pop(stackTop); // Get the last move from the stack
                swap(puzzle[lastMove.x][lastMove.y], puzzle[emptyX][emptyY]); // Undo the move
                emptyX = lastMove.x; // Update the empty tile position
                emptyY = lastMove.y;
                continue;
            } else {
                cout << "No moves to undo!" << endl;
                continue;
            }
        } else {
            cout << "Invalid input!" << endl; // Handle invalid input
            continue;
        }

        int newX = emptyX + dx; // Calculate the new empty tile position
        int newY = emptyY + dy;

        if (isValidMove(newX, newY)) { // Check if the move is valid
            push(stackTop, emptyX, emptyY, dx, dy); // Save the current move to the stack
            swap(puzzle[emptyX][emptyY], puzzle[newX][newY]); // Execute the move
            emptyX = newX; // Update the empty tile position
            emptyY = newY;
        } else {
            cout << "Invalid move!" << endl; // Handle invalid move
        }
    }

    clearStack(stackTop); // Clear the stack after the game ends
}

int main() {
    // Define the start and goal states of the puzzle
    int start[N][N] = {
        {1, 0, 3, 4},
        {5, 2, 7, 8},
        {9, 6, 11, 12},
        {13, 10, 14, 15}
    };

    int goal[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    playGame(start, goal); // Start the puzzle game

    return 0;
}