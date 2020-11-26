/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: Sept. 29th,2020
Description:
The program is to create some operator of MyGrid which is based on two-dimensional array of elements.
Here is H file, and this file is used to initialize some operators which is provided or required in
problem document.
*/
#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class MyGrid
{

public:
    MyGrid();



    bool loadGridFromFile(const string& filename);
    void zeroOutGrid();
    long getNumRows() const;
    long getNumCols() const;

    MyGrid operator+(MyGrid const&) const;
    MyGrid operator-(MyGrid const&) const;

    MyGrid operator+(long const&) const;

    friend MyGrid operator+(long const& lhs, MyGrid const& rhs);

    // Addition assignment 
    MyGrid& operator+=(MyGrid const&);
    // Increment
    MyGrid& operator++(); // Prefix
    MyGrid operator++(int); // Postfix

    MyGrid& operator--(); // Prefix
    MyGrid operator--(int); // Postfix

    MyGrid operator-() const;

    bool operator==(MyGrid const&) const;

    friend fstream& operator<<(fstream& os, const MyGrid& gridIn);


private:
    long myX, myY;
    vector<vector<long>> gridElements;
    long rows,columns;
};

