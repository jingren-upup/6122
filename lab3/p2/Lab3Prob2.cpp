/*
Author: <Jingren Wang>
Class: ECE6122
Last Date Modified : <14 / 10 / 2020>
Description :This program is used to calculate probability of ant reaching the
point before gets stuck. Brilli the ant is trying to get from point AA to point
BB in a grid. The coordinates of point AA is (1,1) (this is top left corner), and
the coordinates of point BB is (n,n) (this is bottom right corner, nn is the size
of the grid).
*/
#include <omp.h>
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <set>
#include <cstring>
#include <iomanip>

using namespace std;
typedef pair<int,int> point;

//judge whether the ant is stuck
bool IfBlocked(pair<int,int> const& point0, set<pair<int,int>> const& grid){
    //create point
    point point1 = point0;
    point point2 = point0;
    point point3 = point0;
    point point4 = point0;
    //set four nearby point
    point1.second--;
    point2.second++;
    point3.first--;
    point4.first++;
    //initialize point
    set<pair<int,int>>::const_iterator end1 = grid.find(point1);
    set<pair<int,int>>::const_iterator end2 = grid.find(point2);
    set<pair<int,int>>::const_iterator end3 = grid.find(point3);
    set<pair<int,int>>::const_iterator end4 = grid.find(point4);
    // judge point is blockd
    if (point0.second == 6 && point0.first == 1)
    {
        if ((end1 != grid.end()) && (end4 != grid.end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (point0.second == 1 && point0.first == 6)
    {
        if ((end2 != grid.end()) && (end3 != grid.end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (point0.second == 6)
    {
        if ((end1 != grid.end()) && (end3 != grid.end()) && (end4 != grid.end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (point0.first == 6)
    {
        if ((end1 != grid.end()) && (end2 != grid.end()) && (end3 != grid.end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (point0.second == 1)
    {
        if ((end2 != grid.end()) && (end3 != grid.end()) && (end4 != grid.end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (point0.first == 1)
    {
        if ((end1 != grid.end()) && (end2 != grid.end()) && (end4 != grid.end()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if ((end1 == grid.end()) || (end2 == grid.end()) || (end3 == grid.end()) || (end4 == grid.end()))
    {
        return false;
    }
    return true;



}



int main(int argc, char* argv[])
{
    //create Num
    long RunNum;
    long GridNum;


    double start_time = omp_get_wtime();
    // input Num
    for (int i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-N"))
        {
             RunNum = strtol(argv[i + 1],NULL,10);

        }
        if (!strcmp(argv[i], "-g"))
        {
             GridNum = strtol(argv[i + 1],NULL,10);

        }
    }

    //initilize random num
    default_random_engine generator;
    uniform_int_distribution<int> distribution0(1, 4);

    int SuccessNum = 0;
    //set end point
    point end(GridNum,GridNum);



#pragma omp parallel for reduction(+:SuccessNum)
    //start thread
    for (int i  = 0;  i  < RunNum; ++i) {
        point point0(1, 1);
        set<pair<int,int>> grid0;
        grid0.insert(point0);

        //start circle
        while((point0 != end) && !IfBlocked(point0, grid0)){

            pair<int,int> CurrentPoint = point0;

            set<pair<int,int>>::const_iterator  get;
            // four different case
            switch (distribution0(generator)) {
                //up
                case 1:
                    CurrentPoint.second--;
                    get = grid0.find(CurrentPoint);
                    if ((CurrentPoint.second > 0) && (get == grid0.end())) {
                        point0.second--;
                        grid0.insert(point0);
                    }
                    break;
                //down
                case 2:
                    CurrentPoint.second++;
                    get = grid0.find(CurrentPoint);
                    if ((CurrentPoint.second <= GridNum) && (get == grid0.end())) {
                        point0.second++;
                        grid0.insert(point0);
                    }
                    break;
                //left
                case 3:
                    CurrentPoint.first--;
                    get = grid0.find(CurrentPoint);
                    if ((CurrentPoint.first > 0) && (get == grid0.end())) {
                        point0.first--;
                        grid0.insert(point0);
                    }
                    break;
                //right
                case 4:
                    CurrentPoint.first++;
                    get = grid0.find(CurrentPoint);
                    if ((CurrentPoint.first <= GridNum) && (get == grid0.end())) {
                        point0.first++;
                        grid0.insert(point0);
                    }
                    break;
                }
               if(CurrentPoint == end){SuccessNum++;}
        }
    }
    double pp = (double)SuccessNum/ RunNum;//calculate result

   ofstream ofs;
   ofs.open("Lab3Pro2.txt");
   ofs << "The answer is: " << setiosflags(ios::fixed) << setprecision(7) << pp << endl;

   ofs.close();

   cout << "The answer is: " << setiosflags(ios::fixed) << setprecision(7) << pp << " in " << 1000.0 * (omp_get_wtime() - start_time) << " millsec " << endl;
   return 0;
}
