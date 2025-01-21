#include <iostream>
#include <chrono>
#include "SolveSudoku.h"
#include "Generate.h"

using namespace std;

constexpr int sudokuSize = 9;

int sudoku[9][9];
int unSolveSudoku[9][9];

void printSudoku(int sudoku[9][9], const bool isSolve = false) {
    // Print the top line
    cout << "+-----------------------+\n";

    // Print the grid
    for(int i = 0; i < 81; i++) {
        // If we're at the third column the write a divider
        if(!(i % 3))
            cout << "| ";

        // If we're at the third row the write a divider
        if(!(i % 9) && i) {
            if(!(i % 27))
                cout << "\n|-------+-------+-------|\n| ";
            else
                cout << "\n| ";
        }

        if(((int*)sudoku)[i] == 0) {
            cout << ". ";
        }else {
            cout << ((int*)sudoku)[i] << ' ';
        }
    }

    // The bottom line
    cout << "|\n+-----------------------+\n";

    cout.flush();

    if (!isSolve)
        cout << "\033[14A";
}

int main() {
    const auto start = chrono::high_resolution_clock::now();
    bool validSudoku = false;

    while(!validSudoku) {
        generateSudoku(28, sudoku);
        cout << "\033[2A";
        cout << "Generando nuevo sudoku... " << endl;
        printSudoku(sudoku);

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                unSolveSudoku[i][j] = sudoku[i][j];
            }
        }
        solveSudoku(sudoku, 0);

        validSudoku = Valid(sudoku);
    }

    cout << "\033[2A";
    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double, milli> float_ms = end - start;
    cout << "La ejecucion a durado " << float_ms.count() << " millisegundos" << endl;
    cout << "Nuevo sudoku encontrado: " << endl;
    printSudoku(unSolveSudoku, true);
    cout << "Solucion: " << endl;
    printSudoku(sudoku, true);


    return 0;
}

