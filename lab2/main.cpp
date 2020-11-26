
#include <fstream>
#include <iostream>
#include <vector>
#include "MyGrid.h"

using namespace std;

int main(int argc, char* argv[])
{
    fstream outFile("Lab2Output.txt", fstream::out);

    vector<MyGrid> vecGrids;
    MyGrid tmpGrid;

    vecGrids.resize(argc);
    for (int ii = 1; ii < argc; ii++)
    {
        if (!vecGrids[ii-1].loadGridFromFile(argv[ii]))
        {
            outFile << "Failed to load file: " << argv[ii] << endl;
        }
    }

    if (argc >= 3)
    {
        tmpGrid += vecGrids[1];
        outFile << tmpGrid << endl;

        tmpGrid = vecGrids[0] + vecGrids[1];
        outFile << tmpGrid << endl;

        tmpGrid = vecGrids[0] - vecGrids[1];
        outFile << tmpGrid << endl;

        tmpGrid = vecGrids[0] + 10;
        outFile << tmpGrid << endl;

        tmpGrid = 10 + vecGrids[1] + 10;
        outFile << tmpGrid << endl;

        outFile << tmpGrid++ << endl;
        outFile << ++tmpGrid << endl;

        outFile << tmpGrid-- << endl;
        outFile << --tmpGrid << endl;


        outFile << -tmpGrid << endl;

        if (vecGrids[0] == vecGrids[1])
        {
            outFile << "The first two grids are equal" << endl;
        }
        else
        {
            outFile << "The first two grids are not equal" << endl;
        }

        outFile << "The first grid has " << vecGrids[0].getNumRows() << " rows and " << vecGrids[0].getNumCols() << " cols." << endl;

        vecGrids[0].zeroOutGrid();
        outFile << vecGrids[0] << endl;

    }

    outFile.close();

}