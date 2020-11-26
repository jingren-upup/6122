/*
Author: <Jingren Wang>
Class: ECE6122
Last Date Modified : <14 / 10 / 2020>
Description : The program is using OpenMP to create a multi-threaded program
that uses the fundamental theory and logic of the Monte Carlo Simulation technique
to solve the following optimization problem: Find the values of X1, X2, and X3 such
that the following equation has the maximum value for Z.

 𝑍𝑍 = (𝑒𝑒𝑋𝑋1 + 𝑋𝑋2)2 + 3(1 − 𝑋𝑋3)2
*/

#include <omp.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include <ctime>


using namespace std;


int main(int argc, char* argv[]) {
    //take the command-line argument variable of type unsigned long
    unsigned long ThreadCount = strtol(argv[1], NULL, 10);
    //set time
    srand(time(NULL));
    clock_t starttime, endtime;
    //set point
    double ZOri = 0;
    double zNew = 0 ;
    double xNew[3] = {0};
    double XOri[3] = {0};

    //set random num
    default_random_engine generator;
    uniform_real_distribution<double> X1distribution(0, 1);
    uniform_real_distribution<double> X2distribution(0, 2);
    uniform_real_distribution<double> X3distribution(2, 3);


    starttime = clock();
#pragma omp parallel private(xNew, zNew)
    {
#pragma omp for nowait
        //start thread
        for (unsigned long  i = 0; i < ThreadCount; ++i) {

            xNew[0] = X1distribution(generator);
            xNew[1] = X2distribution(generator);
            xNew[2] = X3distribution(generator);

            zNew = pow((exp(xNew[0]) + xNew[1]), 2) + 3 * pow((1 - xNew[2]), 2);
          //judge which is larger
            if (ZOri <= zNew) {
                XOri[0] = xNew[0];
                XOri[1] = xNew[1];
                XOri[2] = xNew[2];
            }

            ZOri = max(ZOri, zNew);

        }
    }



        endtime = clock();
        double time = (double) (endtime - starttime) * 1000 / CLOCKS_PER_SEC;
        cout<< "time is "<< fixed << setprecision(9)<< time << " ms"<< endl;


    //declare a variable named output
    ofstream output;
    //creat a file based on the given standard
    output.open("Lab3Prob3.txt", ofstream::out);
    output << setprecision(16) << XOri[0] << endl;
    output << setprecision(16) << XOri[1] << endl;
    output << setprecision(16) << XOri[2] << endl;
    output << setprecision(9) <<  time  <<" ms"<< endl;

    //close the file
    output.close();

    return 0;
}


