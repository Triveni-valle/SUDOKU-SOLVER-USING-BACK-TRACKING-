
#include <iostream>
using namespace std;

void printGrid(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << grid[i][j] << " ";
            if (j % 3 == 2 && j != 8) cout << "| ";
        }
        cout << endl;
        if (i % 3 == 2 && i != 8) cout << "------+-------+------" << endl;
    }
    cout << endl;
}

bool isSafe(int grid[9][9], int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool findEmptyLocation(int grid[9][9], int& row, int& col) {
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

bool solveSudoku(int grid[9][9]) {
    int row, col;

    if (!findEmptyLocation(grid, row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            grid[row][col] = 0;
        }
    }
    return false;
}

bool isValidGrid(int grid[9][9]) {
    int count[10];

    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 10; k++) count[k] = 0;
        for (int j = 0; j < 9; j++) {
            int val = grid[i][j];
            if (val && ++count[val] > 1) return false;
        }
    }

    for (int j = 0; j < 9; j++) {
        for (int k = 0; k < 10; k++) count[k] = 0;
        for (int i = 0; i < 9; i++) {
            int val = grid[i][j];
            if (val && ++count[val] > 1) return false;
        }
    }

    for (int box = 0; box < 9; box++) {
        for (int k = 0; k < 10; k++) count[k] = 0;

        int r = (box / 3) * 3;
        int c = (box % 3) * 3;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                int val = grid[r + i][c + j];
                if (val && ++count[val] > 1) return false;
            }
    }

    return true;
}

int main() {
    int grid[9][9];

    cout << "Enter Sudoku puzzle (0 for empty cells):\n";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            if (!(cin >> grid[i][j])) {
                cout << "Invalid input (non-number detected)!" << endl;
                return 0;
            }

            if (grid[i][j] < 0 || grid[i][j] > 9) {
                cout << "Invalid input (must be 0-9)!" << endl;
                return 0;
            }
        }
    }

    if (!isValidGrid(grid)) {
        cout << "Invalid Sudoku puzzle!" << endl;
        return 0;
    }

    cout << "\nOriginal Puzzle:\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "Solved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}

