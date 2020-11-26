/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: Sept.29th,2020
Description:
The program is to create some operator of MyGrid which is based on two-dimensional array of elements.
Here is c source file, and this file is used to realize each function of methods.This file will be
tested in main cpp finally.
*/


#include "MyGrid.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// initialize MyGrid function
MyGrid::MyGrid() {
}

// load data from txt file and put them into vector
bool MyGrid::loadGridFromFile(const string& filename){
    ifstream in(filename);//extract data
    in >> myX;
    in >> myY;
    in >> rows;
    in >> columns;
    vector<vector<long>> elements(rows,vector<long>(columns));//temporary vector
    for(int i = 0;i<rows;i++)
    {
        for(int j =0;j<columns;j++)
        {
            in >>elements[i][j];
            this->gridElements = elements;//put data into 2D array
        }
    }
    //close ifstream
    in.close();
    return true;
}
//set all elements to 0
void MyGrid::zeroOutGrid() {

    vector<vector<long>> elements(rows,vector<long>(columns,0));
    this->gridElements = elements;//put 0 to GridElements
}
//operator+ for grid and grid
MyGrid MyGrid::operator+(MyGrid const &rhs) const{
    MyGrid myGrid(*this);

    long ro, col, x, y;
    //new x new y
    x = min(myGrid.myX, rhs.myX);//choose x for new grid
    y = max(myGrid.myY, rhs.myY);//choose y for new grid


    //new row new column
    //calculate row and colunm for new grid and put them into temporary parameter
    if((myGrid.myX+myGrid.columns) > (rhs.myX+rhs.columns)){col = (myGrid.myX+myGrid.columns) - x;}else{col = (rhs.myX+rhs.columns) - x;}
    if((myGrid.myY - myGrid.rows) < (rhs.myY - rhs.rows)){ro = y -(myGrid.myY - myGrid.rows);}else{ro =  y - rhs.myY + rhs.rows;}
    //new vector
    vector<vector<long>> NewGrid(ro,vector<long>(col));

    for (long i = 0; i< ro;++i){
        for(long j = 0; j< col;++j){
            NewGrid[i][j] = 0;// all elements set to 0
            if((i>=-rhs.myY+y)&&(i<-rhs.myY+rhs.rows+y)&&(j>=rhs.myX-x)&&(j<rhs.myX-x+rhs.columns)){
                NewGrid[i][j] +=rhs.gridElements[i-y+rhs.myY][j+x-rhs.myX];// if have cross with rhs elements, add the elements to NewGrid
            }
            if((i>=-myGrid.myY+y)&&(i<-myGrid.myY+myGrid.rows+y)&&(j>=myGrid.myX-x)&&(j<myGrid.myX-x+myGrid.columns)){
                NewGrid[i][j] +=myGrid.gridElements[i-y+myGrid.myY][j+x-myGrid.myX];// if have cross with MyGrid elements, add the elements to NewGrid
            }
        }
    }
    //assigned every value to Grid
    myGrid.gridElements = NewGrid;
    myGrid.myX = x;
    myGrid.myY = y;
    myGrid.rows = ro;
    myGrid.columns = col;
    return myGrid;
}
//operator- for grid and grid
MyGrid MyGrid::operator-(MyGrid const &rhs) const{
    MyGrid myGrid(*this);
    long ro, col, x, y;
    //new x new y
    x = min(myGrid.myX, rhs.myX);
    y = max(myGrid.myY, rhs.myY);


    //new row new column
    //calculate row and colunm for new grid and put them into temporary parameter
    if((myGrid.myX+myGrid.columns) > (rhs.myX+rhs.columns)){col = (myGrid.myX+myGrid.columns) - x;}else{col = (rhs.myX+rhs.columns) - x;}
    if((myGrid.myY - myGrid.rows)<(rhs.myY - rhs.rows)){ro = y -(myGrid.myY - myGrid.rows);}else{ro =  y - rhs.myY + rhs.rows;}
    //new vector
    vector<vector<long>> NewGrid(ro,vector<long>(col));

    for (long i = 0; i< ro;++i){
        for(long j = 0; j< col;++j){
            NewGrid[i][j] = 0;// all elements set to 0
            if((i>=-rhs.myY+y)&&(i<-rhs.myY+rhs.rows+y)&&(j>=rhs.myX-x)&&(j<rhs.myX-x+rhs.columns)){
                NewGrid[i][j] -=rhs.gridElements[i-y+rhs.myY][j+x-rhs.myX];// if have cross with rhs elements, subtract the elements to NewGrid
            }
            if((i>=-myGrid.myY+y)&&(i<-myGrid.myY+myGrid.rows+y)&&(j>=myGrid.myX-x)&&(j<myGrid.myX-x+myGrid.columns)){
                NewGrid[i][j] +=myGrid.gridElements[i-y+myGrid.myY][j+x-myGrid.myX];// if have cross with MyGrid elements, subtract the elements to NewGrid
            }
        }
    }
    //assigned every value to Grid
    myGrid.gridElements = NewGrid;
    myGrid.myX = x;
    myGrid.myY = y;
    myGrid.rows = ro;
    myGrid.columns = col;
    return myGrid;
}
//operator+ for grid and const parameter
MyGrid MyGrid::operator+(long const &inlong) const{
    MyGrid myGrid (*this);
    //set rows and columns
    long ro, col;
    ro = this->rows;
    col =this->columns;
    vector<vector<long>> NewGrid(ro,vector<long>(col));
    for (int i = 0; i < ro; ++i) {
        for (int j = 0; j < col; ++j) {
            NewGrid[i][j] = myGrid.gridElements[i][j] + inlong;// add value
        }
    }
    //load GridElements
    myGrid.gridElements = NewGrid;
    return myGrid;

}
//operator+ for grid and const parameter
MyGrid operator+(long const& lhs, MyGrid const& rhs){
    //create myGrid and set value
    MyGrid myGrid;
    myGrid.myX = rhs.myX;
    myGrid.myY = rhs.myY;
    myGrid.columns = rhs.columns;
    myGrid.rows = rhs.rows;
    myGrid.gridElements = rhs.gridElements;


    vector<vector<long>> NewGrid(myGrid.rows,vector<long>(myGrid.columns));
    //add const value and gridElements
    for (int i = 0; i < myGrid.rows; ++i) {
        for (int j = 0; j < myGrid.columns; ++j) {
            NewGrid[i][j] = myGrid.gridElements[i][j] + lhs;
        }
    }
    myGrid.gridElements = NewGrid;
    return myGrid;

}
//operator+= for grid
MyGrid&  MyGrid::operator+=(MyGrid const&rhs){
    //assigned all rhs value to this
    this->myX = rhs.myX;
    this->myY = rhs.myY;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    vector<vector<long>> elements(rhs.rows,vector<long>(rhs.columns));
    this->gridElements = elements;
    this->gridElements = rhs.gridElements;
    return *this;

}
//operator++ for grid(post)
MyGrid& MyGrid::operator++(){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            gridElements[i][j]++;
        }
    }
    return *this;
}
//operator++ for grid(pre)
MyGrid MyGrid::operator++(int){
    MyGrid grid = *this;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            ++this->gridElements[i][j];
        }
    }

    return grid;
}
//operator-- for grid(post)
MyGrid& MyGrid::operator--(){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            gridElements[i][j]--;
        }
    }
    return *this;
}
//operator-- for grid(pre)
MyGrid MyGrid::operator--(int){
    MyGrid grid = *this;
    --(*this);
    return grid;
}
//operator- for grid(negative)
MyGrid MyGrid::operator-() const{
    MyGrid grid(*this);
    for (long i = 0; i < grid.rows; ++i) {
        for (long j = 0; j < grid.columns; ++j) {
            grid.gridElements[i][j] =-1*grid.gridElements[i][j] ;
        }
    }

    return grid;
}
//operator== for grid to judge whether is same or not
bool MyGrid::operator==(MyGrid const&rhs) const{
 MyGrid myGrid(*this);
 if((this->myX != rhs.myX)&&(this->myY != rhs.myY)&&(this->columns != rhs.columns)&&(this->rows != rhs.rows)){
     return false;
 }
 if (this->gridElements != rhs.gridElements){
     return false;
 }

    return true;
}
//operator<< for grid to output result
fstream& operator<<(fstream& os, const MyGrid& gridIn){
    //output myX myY rows columns
    os << gridIn.myX <<" "<< gridIn.myY <<endl;
    os << gridIn.rows<<" "<< gridIn.columns<<endl;

    for(int i = 0;i<gridIn.rows;i++)
    {
        for(int j =0;j<gridIn.columns;j++)
        {
            os << gridIn.gridElements[i][j] <<" ";
        }
        os << endl;

    }
    return os;

}
//get for rows and columns
long MyGrid::getNumRows() const{
    return rows;
}
long MyGrid::getNumCols() const {
    return columns;
}








