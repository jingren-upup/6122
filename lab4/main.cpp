/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/10/27
Description:
This file contains the main function. It is used to display the 3D maze and everything
in it. Pressing the R or r key can rotate the maze clockwise or anti-clockwise
by 5 degrees each time the key is pressed.
*/


#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include"ECE_Ghost.h"
#include"ECE_Pacman.h"
//create the coins for maze
double coins[152][3] = { {-1.2,-1.6,0.0},{-1.0,-1.6,0},{-0.8,-1.6,0},{-0.6,-1.6,0},{-0.4,-1.6,0},{-0.2,-1.6,0},{0,-1.6,0},{0.2,-1.6,0},//line 1
{0.6,-1.6,0},{0.8,-1.6,0},{1.0,-1.6,0}, {1.2,-1.6,0}, {1.4,-1.6,0}, {1.6,-1.6,0},{1.8,-1.6,0}, {2.0,-1.6,0},

{-0.6,-1.4,0}, {0.2,-1.4,0},{0.6,-1.4,0}, {1.4,-1.4,0}, //line 2
{-1.2,-1.2,0}, {-0.6,-1.2,0}, {0.2,-1.2,0}, {0.6,-1.2,0}, {1.4,-1.2,0}, {2.0,-1.2,0}, //line 3

{-1.2,-1.0,0}, {-1.0,-1.0,0}, {-0.8,-1.0,0}, {-0.6,-1.0,0}, {-0.4,-1.0,0}, {-0.2,-1.0,0}, {0,-1.0,0}, {0.2,-1.0,0}, //line4
{ 0.4,-1,0},{0.6,-1.0,0}, {0.8,-1,0}, {1.0,-1,0}, {1.2,-1,0}, {1.4,-1,0}, {1.6,-1,0}, {1.8,-1,0}, {2.0,-1,0},

{-1.2,-0.8,0}, {-0.6,-0.8,0}, {-0.2,-0.8,0}, {1.0,-0.8,0}, {1.4,-0.8,0}, {2.0,-0.8,0},//line5
{-1.2,-0.6,0}, {-1.0,-0.6,0}, {-0.8,-0.6,0}, {-0.6,-0.6,0}, {-0.2,-0.6,0}, {0,-0.6,0}, {0.2,-0.6,0}, {0.6,-0.6,0}, {0.8,-0.6,0},//line6
{1.0,-0.6,0}, {1.4,-0.6,0}, {1.6,-0.6,0}, {1.8,-0.6,0}, {2.0,-0.6,0},

{-0.6,-0.4,0}, {1.4,-0.4,0}, {-0.6,-0.2,0}, {1.4,-0.2,0}, {-0.6,0,0}, {1.4,0,0}, {-0.6,0.2,0}, {1.4,0.2,0},//line7-line10
{-0.6,0.4,0}, {1.4,0.4,0}, {-0.6,0.8,0}, {1.4,0.8,0},  {-0.6,0.6,0}, {1.4,0.6,0},//line11-line13

{-1.2,1,0}, {-1,1,0}, {-0.8,1,0}, {-0.6,1,0},{-0.4,1.0,0}, {-0.2,1.0,0},//line 14
{0.0,1.0,0}, {0.2,1.0,0}, {0.6,1,0}, {0.8,1,0}, {1,1,0}, {1.2,1,0}, {1.4,1,0}, {1.6,1,0}, {1.8,1,0}, {2,1,0},

{-1.2,1.2,0}, {-0.6,1.2,0}, {0.2,1.2,0}, {0.6,1.2,0}, {1.4,1.2,0}, {2.0,1.2,0}, //line 15

{-1.0,1.4,0}, {-0.6,1.4,0}, {-0.4,1.4,0}, {-0.2,1.4,0}, {0,1.4,0}, {0.2,1.4,0}, {0.6,1.4,0}, {1,1.4,0}, {0.8,1.4,0}, {1.2,1.4,0}, //line 16
{1.4,1.4,0}, {1.8,1.4,0},

{-1.0,1.6,0}, {-0.6,1.6,0}, {-0.2,1.6,0}, {1.8,1.6,0}, {1.0,1.6,0}, {1.4,1.6,0}, //line 17
{-1.2,1.8,0}, {-1.0,1.8,0}, {-0.8,1.8,0}, {-0.6,1.8,0}, {-0.2,1.8,0}, {0,1.8,0}, {0.2,1.8,0}, {0.6,1.8,0}, {0.8,1.8,0},{1.0,1.8,0}, //line 18
{1.4,1.8,0}, {1.6,1.8,0}, {1.8,1.8,0}, {2.0,1.8,0},
{-1.2,2.0,0}, {0.2,2.0,0}, {0.6,2.0,0}, {2.0,2.0,0}, //line 19
{-1.2,2.2,0}, {-1.0,2.2,0}, {-0.8,2.2,0}, {-0.6,2.2,0}, {-0.4,2.2,0}, {-0.2,2.2,0}, {0,2.2,0}, {0.2,2.2,0}, {0.4,2.2,0}, //line 20
{0.6,2.2,0}, {0.8,2.2,0}, {1.0,2.2,0}, {1.2,2.2,0}, {1.4,2.2,0}, {1.6,2.2,0}, {1.8,2.2,0}, {2.0,2.2,0} };
//create the powerup
double golds[4][3] = { {-1.2,-1.4,0},{2.05,-1.4,0},{-1.2,1.4,0},{2.05,1.4,0} };
GLUquadricObj* quardratic{ nullptr };
//create pacman and ghost
Pacman pacman;
Ghost ghost;
// Camera direction
int angle = 0.0; // angle of rotation for the camera direction
//initilize 
void init(void)
{   // set background color as black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    if (!quardratic)
        quardratic = gluNewQuadric();
}
//draw coins
void DrawCoins(void) {
    glColor3f(0.75, 0.75, 0.75);//coins color
    for (int i = 0; i < 152; ++i)
    {
        if (coins[i][2] == 0)
        {
            glPushMatrix();
            glTranslatef(coins[i][0], 0.1, coins[i][1]);
            glutSolidSphere(0.03, 20, 20);//coins radius and basic conditions
            glPopMatrix();
        }
    }
  

}
//draw powerup
void DrawPowerup(void) {
    glColor3f(0.68, 0.58, 0.44); //Define the color for powers.
    for (int i = 0; i < 4; i++)
    {
        if (golds[i][2] == 0)  
        {
            glPushMatrix();
            glTranslatef(golds[i][0], 0, golds[i][1]);
            glRotatef(-90, 1, 0, 0);
            GLUquadricObj* objDisk = gluNewQuadric();
            gluDisk(objDisk, 0.0001, 0.05, 40, 40);//power up basic conditions
            glPopMatrix();

        }
    }

}

//draw maze
void Maze(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    //core maze
    glPushMatrix();
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0.0, 0.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, 0.4);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, 0.8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, 0.0, 0.4);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, 0.0, -0.4);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, 0.0, -0.8);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0.0, -0.4);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.0, 0.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    //outer maze
    glPushMatrix();
    glTranslatef(0.4, 0.0, 0.8);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, 0.0, 1.6);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, 0.0, -1.2);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 1.6);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.8f, 32, 32);
    glPopMatrix();

    //sides
    //left top side
    glPushMatrix();
    glTranslatef(-1.4, 0.0, -0.4);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.4f, 32, 32);
    glPopMatrix();

    //top
    glPushMatrix();
    glTranslatef(-1.4, 0.0, -1.8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.6f, 32, 32);
    glPopMatrix();
    //bottom
    glPushMatrix();
    glTranslatef(-1.4, 0.0, 2.4);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.6f, 32, 32);
    glPopMatrix();

    //left bottom side
    glPushMatrix();
    glTranslatef(-1.4, 0.0, 2.4);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.6f, 32, 32);
    glPopMatrix();

    //right top side
    glPushMatrix();
    glTranslatef(2.2, 0.0, -0.4);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.4f, 32, 32);
    glPopMatrix();

    //right bottom side
    glPushMatrix();
    glTranslatef(2.2, 0.0, 2.4);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.6f, 32, 32);
    glPopMatrix();
    // left top cuved side
    glPushMatrix();
    glTranslatef(-0.8, 0.0, -0.4);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.4, 0.0, 0.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();
    // left bottom cuved side
    glPushMatrix();
    glTranslatef(-0.8, 0.0, 0.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 0.0, 0.4);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 0.0, 0.8);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();


    //righ bottom curved side
    glPushMatrix();
    glTranslatef(1.6, 0.0, 0.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6, 0.0, 0.4);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6, 0.0, 0.8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();

    //right top  curved side
    glPushMatrix();
    glTranslatef(1.6, 0.0, -0.4);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.2, 0.0, 0.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.6f, 32, 32);
    glPopMatrix();


    //top small part
    //left
    //line 1
    glPushMatrix();
    glTranslatef(-1.0, 0.0, -0.8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //square 1
    glPushMatrix();
    glTranslatef(-1.0, 0.0, -1.2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, 0.0, -1.2);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 0.0, -1.4);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 0.0, -1.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //square 2
    glPushMatrix();
    glTranslatef(-0.4, 0.0, -1.2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.4, 0.0, -1.2);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.4);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //right
    //line 2
    glPushMatrix();
    glTranslatef(1.6, 0.0, -0.8);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //square 3

    glPushMatrix();
    glTranslatef(0.8, 0.0, -1.2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0.0, -1.2);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.0, -1.4);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2, 0.0, -1.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //square 4
    glPushMatrix();
    glTranslatef(1.6, 0.0, -1.2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6, 0.0, -1.2);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, 0.0, -1.4);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8, 0.0, -1.4);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //bottom small part
    //left bottom
    glPushMatrix();
    glTranslatef(0.0, 0.0, 1.2);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();
    // like 7 shape
    glPushMatrix();
    glTranslatef(-0.8, 0.0, 1.2);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.8, 0.0, 1.2);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2, 0.0, 1.6);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //like t shape
    glPushMatrix();
    glTranslatef(-0.4, 0.0, 2.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 2.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //right bottom parts
    glPushMatrix();
    glTranslatef(0.8, 0.0, 1.2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    // like 7 shape
    glPushMatrix();
    glTranslatef(1.6, 0.0, 1.2);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.6, 0.0, 1.2);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, 0.0, 1.6);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.2f, 32, 32);
    glPopMatrix();

    //like t shape
    glPushMatrix();
    glTranslatef(1.2, 0.0, 1.6);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 0.4f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.8, 0.0, 2.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();
    //put the pacman and ghost into maze
    glPushMatrix();
    pacman.drawPacman();
    ghost.drawGhostGreen();
    ghost.drawGhostOrange();
    ghost.drawGhostPink();
    ghost.drawGhostRed();
    glPopMatrix();
    //put the coins
    glPushMatrix();
    DrawCoins();
    glPopMatrix();
    //put the powerup
    glPushMatrix();
    DrawPowerup();
    glPopMatrix();

  

    glutSwapBuffers();
}
// display the scene
void Display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    //set camera
    gluLookAt(
        0.0, 5.0, 6.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, -1.0);
    //set light and color material
    GLfloat light_ambient[] = { 0.58, 0.58, 0.58, 1.0 };
    GLfloat light_diffuse[] = { 2.0, 2.0, 2.0, 1.0 };
    GLfloat light_specular[] = { 3.0, 3.0, 3.0, 1.0 };
    GLfloat light_position[] = { 0.0, 1.0, 1.0, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPushMatrix();
    glTranslatef(0, 1.0, 1.0);
    glRotatef((GLfloat)angle, 0.0, 1.0, 0.0);//set rotate point
    Maze();
    glPopMatrix();

  


}
// set key 
void keyboard(unsigned char key, int x, int y)
{//r can rotate anti-clockwise
    switch (key) {
        case 'r':
        angle = (angle + 5) % 360;
        glutPostRedisplay();
        break;
//R rotate clockwise
      case 'R':
         angle = (angle - 5) % 360;
         glutPostRedisplay();
        break;

      default:
          break;


    }
}
//reshape scene
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
   

}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(910, 910);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pacman");


    init();
    glutDisplayFunc(Display);//display callback
    glutReshapeFunc(reshape);//window reshape callback
    glutKeyboardFunc(keyboard);//keyboard callback
    glutMainLoop();
    return 0;
}