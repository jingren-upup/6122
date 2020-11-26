/*
Author: <Jingren Wang>
Class: ECE6122
Last Date Modified : <14 / 10 / 2020>
Description : The program is to operate multi-thread to calculate Sudoku, and
use mutex to prevent read and write error ,the solveSudokuPuzzles function is
to guarantee file processing stably.
*/

#include <fstream>
#include <iostream>
#include <vector>
#include "SudokuGrid.h"
#include <string>
#include <mutex>
#include <thread>


using namespace std;
// create four parameter to read and write txt
mutex outFileMutex;
mutex inFileMutex;
fstream inFile;
fstream outFile;


//use a std::mutex(s) to protect the global variables inFile and outFile.
void solveSudokuPuzzles(){
    SudokuGrid grid;//create a Sudokugrid

    do{
        inFileMutex.lock();//lock infile by mutex
        inFile >> grid;// input grid
        inFileMutex.unlock();
        grid.solve();//process grid
        outFileMutex.lock();//lock outfile by mutex
        outFile << grid;//output grid
        outFileMutex.unlock();//unlock
    }while (!inFile.eof());//if no file, stop processing
}

int main(int argc, char* argv[])
{
    unsigned long numThr = thread::hardware_concurrency();//assign hardware thread to numthr

    vector<SudokuGrid> vecGrids(numThr);
    vector<thread> threads;//create thread
    inFile.open(argv[1]);//input file
    outFile.open("Lab3Prob1.txt",fstream::out);
	vecGrids.resize(50);
   // spawn thread
    for (int i = 0; i < (numThr - 1); ++i)
    {
        threads.push_back(thread(solveSudokuPuzzles));// add thread
    }

    for (auto& th : threads)
    {
        th.join(); // synchronize threads
    }

    outFile.close();
    inFile.close();
}