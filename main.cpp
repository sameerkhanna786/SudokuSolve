#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#define N 9
#define empty 0

bool isEmpty(int board[N][N], int &row, int &col);

bool validPlacement(int board[N][N], int row, int col, int num);

bool inRow(int board[N][N], int row, int num);

bool inCol(int board[N][N], int col, int num);

bool inBox(int board[N][N], int startRow, int startCol, int num);

bool sudokuSolver(int board[N][N]) {
    int row, col;

    if (!isEmpty(board, row, col)) {
        return true;
    }

    for (int num = 1; num <= N; num++) {
        if (validPlacement(board, row, col, num)) {
            board[row][col] = num;

            if (sudokuSolver(board)) {
                return true;
            }

            board[row][col] = empty;
        }
    }
    return false;
}

bool isEmpty(int board[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (board[row][col] == empty) {
                return true;
            }
        }
    }
    return false;
}

bool inRow(int board[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (board[row][col] == num)
            return true;
    return false;
}

bool inCol(int board[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (board[row][col] == num)
            return true;
    return false;
}

bool inBox(int board[N][N], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (board[row + startRow]
                    [col + startCol] == num)
                return true;
    return false;
}

bool validPlacement(int board[N][N], int row, int col, int num) {
    return !inRow(board, row, num)
        && !inCol(board, col, num)
        && !inBox(board, row - row % 3 , col - col % 3, num);
}

/* A utility function to print grid */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

void fillBoardData(int board[N][N], string grid[N]) {
    for (int i = 0; i < N; i++) {
        string row = grid[i];
        for (int j = 0; j < N; j++) {
            board[i][j] = row[j] - '0';
        }
    }
}

int main()
{
    /* Inititalize any variables needed. */
    string line;
    string gridNum;
    ifstream fin;
    int counter = 0;
    string gridData [10];
    int board[N][N] =  {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    //Note that int board[N][N] = {0}; would acheive the same thing; I chose the above format for clarity.
    fin.open("puzzles.txt");
    if (fin.is_open()) {
        while ( getline (fin,line) ) {
            if (counter == 0) {
                gridNum = line;
            } else {
                if (line.length() != N) {
                    cout << "ERROR: DATA HAS INCORRECT DIMENSIONS. PLEASE CORRECT AND RUN AGAIN." << endl;
                    return 0;
                }
                gridData[counter-1] = line;
            }
            counter++;
            if (counter%(N+1) == 0) {
                fillBoardData(board, gridData);
                printGrid(board);
                cout << "Solving " << gridNum << endl;
                sudokuSolver(board);
                printGrid(board);
                counter = 0;
                cout << "Next Board!" << endl;
            }
        }
        fin.close();
    } else cout << "Unable to open file";
    return 0;
}
