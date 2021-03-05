#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/* n is the size of the matrix that gives the sudoku grid.*/
#define N 9
#define UNASSIGNED 0
/* This sudoku solver uses a backtracking algorithm of checking each possibility for
each slot in the grid (depth-first) and recursively calling until a solution is found.*/

bool FindUnassignedLocation(int grid[N][N],
	int& row, int& col);
bool isSafe(int grid[N][N], int row,
	int col, int num);

/* Solver function; attemps to recursively solve the grid until a solution is found.
If no solution is found, returns false. If solution is found, the grid is mutated and
a bool of true is returned.*/
bool SolveSudoku(int grid[N][N])
{
	int row, col;

	// If there is no unassigned location,
	// we are done
	if (!FindUnassignedLocation(grid, row, col))
		// success!
		return true;

	// Consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{

		// Check if looks promising
		if (isSafe(grid, row, col, num))
		{

			// Make tentative assignment
			grid[row][col] = num;

			// Return, if success
			if (SolveSudoku(grid))
				return true;

			// Failure, unmake & try again
			grid[row][col] = UNASSIGNED;
		}
	}

	// This triggers backtracking
	return false;
}

/* Finds next empty slot in grid to be filled and returns whether empty slot exists.*/
bool FindUnassignedLocation(int grid[N][N],
	int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}


/* Checks whether a given number i is in a row.*/
bool inRow(int grid[N][N], int row, int i)
{
	for (int column = 0; column < N; column++)
		if (grid[row][column] == i)
			return true;
	return false;
}

/* Checks whether a given number i is in a column.*/
bool inColumn(int grid[N][N], int column, int i) {
	for (int row = 0; row < N; row++)
		if (grid[row][column] == i)
			return true;
	return false;
}

/* Checks whether a given number i is in a box.*/
bool inBox(int grid[N][N], int startRow, int startCol, int i) {
	for (int row = 0; row < 3; row++) 
		for (int column = 0; column < 3; column++)
			if (grid[row + startRow]
					[column + startCol]
					== i) 
					return true;
	return false;
}

/* Checks whether a number i is legal to put in a given row and column on grid.*/
bool isSafe(int grid[N][N], int row, int column, int i) {
	return !inRow(grid, row, i)
		&& !inColumn(grid, column, i)
		&& !inBox(grid, row - row % 3, column - column % 3, i)
		&& grid[row][column] == UNASSIGNED;
}

/* Printer function to output grid.*/
void printGrid(int grid[N][N]) {
	for (int row = 0; row < N; row++) {
		for (int column = 0; column < N; column++)
			cout << grid[row][column] << " ";
		cout << endl;
	}
}

int main()
{
	while (1) {
		int grid[N][N];
		ifstream fileIn;
		string filename;
		cout << "Please enter the name of the input file. (Must be text file, include .txt extension.)" << endl;
		cout << "Filename: ";
		cin >> filename;
		fileIn.open(filename);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				fileIn >> grid[i][j];
			}
		}

		if (SolveSudoku(grid) == true)
			printGrid(grid);
		else
			cout << "No solution exists";
		fileIn.close();
		string decision;
		cout << "Would you like to save the solution? (Y / N)" << endl;
		cin >> decision;
		if (decision == "Y") {
			ofstream outfile ("solution.txt");
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					outfile << grid[i][j] << " ";
				}
				outfile << endl;
			}
			outfile.close();
			cout << "File Saved!" << endl;
		}
		for (int i = 0; i < 80; i++) {
			cout << "-";
		}
		cout << endl;
	}
	return 0;
}
