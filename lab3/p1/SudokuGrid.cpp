/* 
Author: <Jingren Wang>
Class: ECE6122
Last Date Modified : <14 / 10 / 2020>
Description : Create a class called SudokuGrid that is used to solve SudoGrid£¬
and input and output txt file of Grid.
*/

#include <fstream>
#include <iostream>
#include "SudokuGrid.h"
#include <string>
using namespace std;

// SudokuGrid initialization with nullStr
SudokuGrid::SudokuGrid()
{
    m_strGridName = "nullStr";
}

//input txt file
fstream& operator>>(fstream& os, SudokuGrid& gridIn)
{
    getline(os, gridIn.m_strGridName);//input first line
    for (long i = 0; i < 9; ++i)
    {
        for (long j = 0; j < 9; ++j)
        {
            os >> gridIn.gridElement[i][j] ;
        }
    }
    os.get();//finish input
    return os;
}
//output file
fstream& operator<<(fstream& os, const SudokuGrid& gridIn)
{
    os << gridIn.m_strGridName.c_str() << endl;
    for (long i = 0; i < 9; ++i)
    {
        for (long j = 0; j < 9; ++j)
        {
            os << gridIn.gridElement[i][j];
        }
        os << endl;
    }
    return os;
}
//solve SudokuGrid
void SudokuGrid::solve()
{
    if (solveSudoku() == true){
        solveSudoku();
    }
    else
    {cout << "No solution exists";}


}
//check whether num is present in col or not
bool SudokuGrid::isPresentInCol(int col, int num)
{
    for (int row = 0; row < 9; ++row)
        if (gridElement[row][col] - '0' == num)
            return true;
    return false;
}
//check whether num is present in row or not
bool SudokuGrid::isPresentInRow(int row, int num)
{
    for (int col = 0; col < 9; ++col)
    {
        int a = gridElement[row][col] - '0';
        if (a == num)
            return true;
    }
    return false;
}
//check whether num is present in 3x3 box or not
bool SudokuGrid::isPresentInBox(int boxStartRow, int boxStartCol, int num)
{

    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (gridElement[row + boxStartRow][col + boxStartCol] - '0' == num)
                return true;
    return false;
}
//get empty location and update row and column
bool SudokuGrid::findEmptyPlace(int& row, int& col)
{
    for (row = 0; row < 9; ++row)
    {
        for (col = 0; col < 9; ++col)
        {
            if (gridElement[row][col] == '0') //marked with 0 is empty
                return true;
        }
    }
    return false;
}
//when item not found in col, row and current 3x3 box
bool SudokuGrid::isValidPlace(int row, int col, int num) {

    return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row % 3,	col - col % 3, num);
}
//when all places are filled
bool SudokuGrid::solveSudoku() {
    int row, col;
    if (!findEmptyPlace(row, col))
        return true;
    for (int num = 1; num <= 9; ++num)
    { //valid numbers are 1 - 9
        if (isValidPlace(row, col, num))
        { //check validation, if yes, put the number in the grid
            gridElement[row][col] = num + '0';
            if (solveSudoku()) //recursively go for other rooms in the grid
                return true;
            gridElement[row][col] = '0'; //turn to unassigned space when conditions are not satisfied
        }
    }
    return false;
}



