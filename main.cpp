#include <iostream>
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>

using namespace std;


constexpr int sudokuSize = 9;

int sudoku[9][9] = {
    {0, 0, 2, 0, 5, 0, 0, 0, 0},
    {0, 0, 4, 0, 0, 0, 6, 0, 7},
    {0, 8, 6, 0, 0, 0, 0, 0, 2},
    {0, 4, 0, 0, 0, 0, 0, 0, 0},
    {6, 9, 3, 0, 0, 0, 7, 4, 8},
    {2, 0, 8, 0, 7, 0, 0, 3, 9},
    {3, 2, 0, 4, 0, 0, 9, 0, 5},
    {0, 0, 9, 7, 2, 0, 0, 0, 0},
    {0, 0, 5, 0, 0, 3, 4, 0, 0}
};

/*int sudoku[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};*/

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

bool solveSudoku(int sudoku[9][9], const int index) {
    if(index > 80)
        return true;

    if(((int*)sudoku)[index])
        return solveSudoku(sudoku, index + 1);

    //Recorremos todas las posibles soluciones para el índice deseado
    for(int digit = 1; digit < 10; digit++) {
        static int row, column, blockStartIndex;

        row = index / 9;
        column = index % 9;
        blockStartIndex = row / 3 * 27 + column / 3 * 3; //Calcula el index en el que empieza el bloque

        if(ranges::find(sudoku[row],  digit) != end(sudoku[row]))
            continue;

        // Iterate through 10 indexes
        int i;
        for(i = 0; i < 9; i++){
            // Comprueba si la fila o el bloque tiene el numero
            if(sudoku[i][column] == digit || ((int*)sudoku)[blockStartIndex + i / 3 * 9 + i % 3] == digit)
                break;
        }

        if(i == 9)
            ((int*)sudoku)[index] = digit;
        else
            continue;

        // Then try to solve the remaining cells based on that choice
        if(solveSudoku(sudoku, index + 1))
            return true;
        // Otherwise unmake the choice and try again which in this case means doing nothing
        ((int*)sudoku)[index] = 0;
    }

    // printSudoku(sudoku);

    return false;
}

bool Valid(int grid[9][9])
{
    int *grid1d = (int*)grid;
    int row, column, blockStart;
    int *rowCheck, *columnCheck, *blockCheck;

    // For every cell in the grid
    for(int i = 0; i < 81; i++)
    {
        // This means we can check if so far a grid is valid since blank cells are assigned 0
        if(grid1d[i] == 0)
            continue;

        row = i / 9;
        column = i % 9;
        blockStart = row / 3 * 27 +  column / 3 * 3;

        // Iterate through 10 indexes
        for(int j = 0; j < 9; j++)
        {
            // Check if the row contains the number
            rowCheck = grid1d + row * 9 + j;
            if(grid1d[i] == *rowCheck && (grid1d + i) != rowCheck)
                return false;

            // Check if the row contains the number
            columnCheck = grid1d + j * 9 + column;
            if(grid1d[i] == *columnCheck && (grid1d + i) != columnCheck)
                return false;

            // Check if the row contains the number
            blockCheck = grid1d + blockStart + j / 3 * 9 + j % 3;
            if(grid1d[i] == *blockCheck && (grid1d + i) != blockCheck)
                return false;
        }
    }

    return true;
}

int main() {
    const auto start = chrono::high_resolution_clock::now();

    solveSudoku(sudoku, 0);
    printSudoku(sudoku, true);
    if(Valid(sudoku)) {
        cout << "Sudoku resuelto" << endl;
    }else {
        cout << "Sudoku no resuelto" << endl;
    }
    const auto end = chrono::high_resolution_clock::now();
    const chrono::duration<double, milli> float_ms = end - start;

    cout << "La ejecucion a durado " << float_ms.count() << " millisegundos" << endl;
    return 0;
}

