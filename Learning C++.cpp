// Learning C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
#include<set>

const int SIZE = 9;
const int SUBGRID_SIZE = 3;



struct Coordinates {
    int row, col, val;
};



void initializeGrid(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

void printGrid(const int grid[SIZE][SIZE]) {
    // Print the Sudoku grid
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout <<" " << grid[i][j] << " ";
            if (j == 2 || j == 5) {
                std::cout << "| ";
            }
        }
        std::cout << "\n";
        if (i == 2 || i == 5 || i == 9) {
            for (int k = 0; k < 30; ++k) {
                std::cout << "-";
            }
            std::cout << "\n";
        }
    }
}

std::vector<Coordinates> initializeBlock(const int row, const int col) {
    std::vector<Coordinates> block;
    for (int i = 0; i < SUBGRID_SIZE; i++) {
        for (int j = 0; j < SUBGRID_SIZE; j++) {
            Coordinates coord;
            coord.row = row + i;
            coord.col = col + j;
            block.push_back(coord);
        }
    }
    
    return block;
}

std::vector<Coordinates> initializeColumn(const int col) {
    std::vector<Coordinates> column;
    for (int i = 0; i < 9; i++) {
        Coordinates coord;
        coord.row = i;
        coord.col = col;
        column.push_back(coord);
    }
    return column;
}

std::vector<Coordinates> initializeRow(const int row) {
    std::vector<Coordinates> returnRow;
    for (int i = 0; i < 9; i++) {
        Coordinates coord;
        coord.row = row;
        coord.col = i;
        returnRow.push_back(coord);
    }
    return returnRow;
}

int getRandomNumber() {
    // Seed the random number generator with a random device
    std::random_device rd;

    // Create a random number engine
    std::mt19937 gen(rd());

    // Create a distribution for the range [1, 9]
    std::uniform_int_distribution<> distribution(1, 9);

    // Generate a random number
    return distribution(gen);
}

std::vector<Coordinates> topLeftBlock = initializeBlock(0, 0);
std::vector<Coordinates> topMiddleBlock = initializeBlock(0, 3);
std::vector<Coordinates> topRightBlock = initializeBlock(0, 6);
std::vector<Coordinates> middleLeftBlock = initializeBlock(3, 0);
std::vector<Coordinates> middleMiddleBlock = initializeBlock(3, 3);
std::vector<Coordinates> middleRightBlock = initializeBlock(3, 6);
std::vector<Coordinates> bottomLeftBlock = initializeBlock(6, 0);
std::vector<Coordinates> bottomMiddleBlock = initializeBlock(6, 3);
std::vector<Coordinates> bottomRightBlock = initializeBlock(6, 6);

std::vector<Coordinates> col0 = initializeColumn(0);
std::vector<Coordinates> col1 = initializeColumn(1);
std::vector<Coordinates> col2 = initializeColumn(2);
std::vector<Coordinates> col3 = initializeColumn(3);
std::vector<Coordinates> col4 = initializeColumn(4);
std::vector<Coordinates> col5 = initializeColumn(5);
std::vector<Coordinates> col6 = initializeColumn(6);
std::vector<Coordinates> col7 = initializeColumn(7);
std::vector<Coordinates> col8 = initializeColumn(8);

std::vector<Coordinates> row0 = initializeRow(0);
std::vector<Coordinates> row1 = initializeRow(1);
std::vector<Coordinates> row2 = initializeRow(2);
std::vector<Coordinates> row3 = initializeRow(3);
std::vector<Coordinates> row4 = initializeRow(4);
std::vector<Coordinates> row5 = initializeRow(5);
std::vector<Coordinates> row6 = initializeRow(6);
std::vector<Coordinates> row7 = initializeRow(7);
std::vector<Coordinates> row8 = initializeRow(8);

std::vector<Coordinates> rowsArray[9] = { row0, row1, row2, row3, row4, row5, row6, row7, row8 };
std::vector<Coordinates> columnsArray[9] = { col0, col1, col2, col3, col4, col5, col6, col7, col8 };
std::vector<Coordinates> blocksArray[9] = { topLeftBlock, topMiddleBlock, topRightBlock, middleLeftBlock, middleMiddleBlock, middleRightBlock, bottomLeftBlock, bottomMiddleBlock, bottomRightBlock };


std::vector<Coordinates> randomlyFillColumn(const int startColumn) {
    std::vector<Coordinates> filledColumn;
    int numbersInColumn[9] = {};
    int arrayLength = 9;
    for (int i = 0; i < arrayLength; i++) {
        int randomNum;
        do {
            randomNum = getRandomNumber();
            numbersInColumn[i] = randomNum;
        } while ([&]() { 
            for (int j = 0; j < i; j++) {
                if (numbersInColumn[j] == randomNum) {
                    return true; 
                }
            }
            return false; 
            }());
    }
    for (int i = 0; i < arrayLength; i++) {
        Coordinates coord;
        coord.col = startColumn;
        coord.row = i;
        coord.val = numbersInColumn[i];
        filledColumn.push_back(coord);
    }

    return filledColumn;
}

void rearrangeArray(int arr[], int size) {
    int nonZeroIndex = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            std::swap(arr[i], arr[nonZeroIndex]);
            nonZeroIndex++;
        }
    }
}
//Not working right. Returning wrong column 
//Should be returning column 0,0 but returning 0,8
std::vector<Coordinates> columnToCheck(int colStart, int rowStart) {
    std::cout << "ColStart = " << colStart << "\n";
    std::vector<Coordinates> returnColumn;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (columnsArray[i][j].col == colStart && columnsArray[i][j].row == rowStart) {
                returnColumn = columnsArray[i];
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        std::cout << "returnColumn = " << returnColumn[i].row << ", " << returnColumn[i].col << "\n";
    }
    return returnColumn;
}
//Same problem as the columnToCheck()
std::vector<Coordinates> rowToCheck(int rowStart, int colStart) {
    std::cout << "rowStart = " << rowStart << "\n";
    std::vector<Coordinates> returnColumn;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (columnsArray[i][j].row == rowStart && columnsArray[i][j].col == colStart) {
                returnColumn = columnsArray[i];
            }
        }
    }
    return returnColumn;
}

std::vector<Coordinates> fillBox(int sudokuGrid[9][9], std::vector<Coordinates>& blockToFill) {

    //printGrid(sudokuGrid);
    
    int numbersInBox[9] = {}; 

    int numbersInCol1[9] = {};
    int numbersInCol2[9] = {};
    int numbersInCol3[9] = {};

    int numbersInRow1[9] = {};
    int numbersInRow2[9] = {};
    int numbersInRow3[9] = {};

    std::cout << "blockToFill rows = " << blockToFill[0].row << blockToFill[1].row << blockToFill[2].row << "\n";
    

    std::vector<Coordinates> column1 = columnToCheck(blockToFill[0].col, blockToFill[0].row);
    std::vector<Coordinates> column2 = columnToCheck(blockToFill[1].col, blockToFill[0].row);
    std::vector<Coordinates> column3 = columnToCheck(blockToFill[2].col, blockToFill[0].row);

    std::vector<Coordinates> row1 = rowToCheck(blockToFill[0].row, blockToFill[0].col);
    std::vector<Coordinates> row2 = rowToCheck(blockToFill[1].row, blockToFill[0].col);
    std::vector<Coordinates> row3 = rowToCheck(blockToFill[2].row, blockToFill[0].col);

    std::set<int> generatedNumbers;
    std::set<int> column1Set;

    
    // Set the current value from the sudoku board into the value's of the block and columns to check
    for (int i = 0; i < 9; i++) {
        blockToFill[i].val = sudokuGrid[blockToFill[i].row][blockToFill[i].col];

        column1[i].val = sudokuGrid[column1[i].row][column1[i].col];
        column2[i].val = sudokuGrid[column2[i].row][column2[i].col];
        column3[i].val = sudokuGrid[column3[i].row][column3[i].col];

        row1[i].val = sudokuGrid[row1[i].row][row1[i].col];
        row2[i].val = sudokuGrid[row2[i].row][row2[i].col];
        row3[i].val = sudokuGrid[row3[i].row][row3[i].col];

        std::cout << column1[i].col<< column1[i].row<< "\n";
    }

    //Check if the numbers on the board are the same as the numbers to check in each box/column/row
    for (int i = 0; i < 9; i++) {
        if (blockToFill[i].val != 0) {
            numbersInBox[i] = blockToFill[i].val;
            generatedNumbers.insert(blockToFill[i].val);
            column1Set.insert(blockToFill[i].val);
        }


        if (column1[i].val != 0) {
            numbersInCol1[i] = column1[i].val;
            column1Set.insert(column1[i].val);

        }
        if (column2[i].val != 0) {
            numbersInCol2[i] = column2[i].val;

        }
        if (column3[i].val != 0) {
            numbersInCol3[i] = column3[i].val;

        }


        if (row1[i].val != 0) {
            numbersInRow1[i] = row1[i].val;

        }
        if (row2[i].val != 0) {
            numbersInRow2[i] = row2[i].val;

        }
        if (row3[i].val != 0) {
            numbersInRow3[i] = row3[i].val;

        }
    }

    

    
    //rearrangeArray(numbersInBox, 9);
    rearrangeArray(numbersInCol1, 9);

    for (int i = 0; i < 9; i++) {
        std::cout << " Numbers in Col 1 = " << numbersInCol1[i] << "\n";
    }
    

    

    for (int i = 0; i < 9; i++) {
        if (numbersInBox[i] == 0) {
            int randomNum;
            do {
                randomNum = getRandomNumber();
                numbersInBox[i] = randomNum;
                
            } while (generatedNumbers.count(randomNum) > 0);

            numbersInBox[i] = randomNum;
            generatedNumbers.insert(randomNum);
        }
        
    }
    
    for (int i = 0; i < 9; i++) {
        blockToFill[i].val = numbersInBox[i];
    }
    return blockToFill;
}

int main()
{   

    int sudokuGrid[SIZE][SIZE];


    initializeGrid(sudokuGrid);


    col0 = randomlyFillColumn(0);
    

    for (int i = 0; i < 9; i++) {
        sudokuGrid[i][0] = col0[i].val;
    }

    std::cout << "____________________________________________________________ \n";

    /*topLeftBlock = fillBox(sudokuGrid, topLeftBlock);
    
    

    for (int i = 0; i < 9; i++) {
        sudokuGrid[topLeftBlock[i].row][topLeftBlock[i].col] = topLeftBlock[i].val;
    }*/

    topMiddleBlock = fillBox(sudokuGrid, topMiddleBlock);

    for (int i = 0; i < 9; i++) {
        sudokuGrid[topMiddleBlock[i].row][topMiddleBlock[i].col] = topMiddleBlock[i].val;
    }


    //for (const Coordinates& coord : topLeftBlock) {
    //    std::cout << "(" << coord.row << ", " << coord.col << ", " << coord.val << ") ";
    //}



    //std::cout << typeid(sudokuGrid).name();

    printGrid(sudokuGrid);
    

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
