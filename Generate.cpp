//
// Created by rened on 07/11/2024.
//

#include "Generate.h"
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <set>

using namespace std;

void generateSudoku(const int numNumbers,  int (&sudoku)[9][9]) {
    srand(time(0));
    set<int> numberToGenerate;
    // for(int i = 1; i < numNumbers; i++) {
    while(numberToGenerate.size() < numNumbers){

        const int index = rand() % 81;
        // cout << index << endl;
        numberToGenerate.insert(index);
    }


    for(int index = 0; index < 81; index++) {
        if (ranges::find(numberToGenerate, index) != numberToGenerate.end()) {
            bool validDigit = false;

            while(!validDigit) {
            //for(int j = 1; j < 10; j++) {
                int digit = rand() % 9 + 1;
                static int row, column, blockStartIndex;

                row = index / 9;
                column = index % 9;
                blockStartIndex = row / 3 * 27 + column / 3 * 3;

                if(ranges::find(sudoku[row],  digit) != end(sudoku[row]))
                    continue;

                // Iterate through 10 indexes
                int i;
                for(i = 0; i < 9; i++){
                    // Comprueba si la columna o el bloque tiene el numero
                    if(sudoku[i][column] == digit || ((int*)sudoku)[blockStartIndex + i / 3 * 9 + i % 3] == digit)
                        break;
                }

                if(i == 9) {
                    ((int*)sudoku)[index] = digit;
                    validDigit = true;
                }
            }
        }else {
            ((int*)sudoku)[index] = 0;
        }
    }
}