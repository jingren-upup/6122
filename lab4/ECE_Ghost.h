
/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/10/27
Description:
This is the header file for ghost.cpp.
*/

#include <iostream>
#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> // standard definitions

using namespace std;

class Ghost
{
public:
	void drawGhostRed();// draw different color ghost
	void drawGhostPink();
	void drawGhostGreen();
	void drawGhostOrange();
private:
	GLUquadricObj* quadratic = gluNewQuadric();// initlize the quadratic


};


