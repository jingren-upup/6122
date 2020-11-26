/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/10/27
Description:
This is the cpp file for pacman, its function is to draw pacman and paint color.
*/
#include "ECE_Pacman.h"
//#include <gl/glew.h> // include the glew header file
//#include <gl/glut.h> // include the glut header file
//#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions



void Pacman::drawPacman()
{


    glColor3f(1, 1, 0); // yellow
    glPushMatrix();
    glTranslatef(0.4, 0, 1.45);
    glutSolidSphere(0.1, 20, 20);//create pacman
    glPopMatrix();
}















