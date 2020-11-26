/*
Author: <Jingren Wang>
Class: ECE6122
Last Date Modified : <14 / 10 / 2020>
Description :Here is H file, and this file is used to initialize some operators which is
provided or required in problem document.
*/

#pragma once

#include <string>

using namespace std;

class SudokuGrid
{
public:
    SudokuGrid();
    SudokuGrid(string name);
    bool isPresentInCol(int col, int num);
    bool isPresentInRow(int row, int num);
    bool isPresentInBox(int boxStartRow, int boxStartCol, int num);
    bool findEmptyPlace(int& row, int& col);
    bool isValidPlace(int row, int col, int num);
    bool solveSudoku();
    void solve();
    friend fstream& operator>>(fstream& os, SudokuGrid& gridIn);
    friend fstream& operator<<(fstream& os, const SudokuGrid& gridIn);

private:
    string m_strGridName;
    unsigned char gridElement[9][9];
};