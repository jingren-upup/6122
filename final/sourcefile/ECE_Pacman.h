/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/10/27
Description:
This is the header file for pacman.cpp.
*/


#pragma once

#include <iostream>
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions

using namespace std;

class Pacman
{
public:
    void drawPacman();
    void move(int position);
    //four direction egde of pacman
    bool upedge(double zposition, double xpositon);
    bool downedge(double zposition, double xpositon);
    bool leftedge(double xpositon, double zposition);
    bool rightedge(double xpositon, double zposition);
    //original position of pacman
    double xPosition = 2.0;
    double zPosition = 7.0;
private:

};
