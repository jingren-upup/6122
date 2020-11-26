/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/10/27
Description:
This file contains the main function. It is used to display the 3D pacman game and everything
in it. Pressing the R or r key can rotate the maze clockwise or anti-clockwise
by 5 degrees each time the key is pressed.And type UP ,DOWN.LEFT ,RIGHT can change the 
moving direction, ESC will exit the game.Pressing the g key can start the ghost move£¬and begin the 
game.
*/


#include <GL/glut.h> // Include the GLUT header file
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include"ECE_Ghost.h"
#include"ECE_Pacman.h"
#include <chrono>
#include<thread>
#include <windows.h>
#define ESC 27

//create the coins for maze
double coins[152][3] = { {-6.0,-8.0,0.0},{-5.0,-8.0,0},{-4.0,-8.0,0},{-3.0,-8.0,0},{-2.0,-8.0,0},{-1.0,-8.0,0},{0,-8.0,0},{1.0,-8.0,0},//line 1
{3.0,-8.0,0},{4.0,-8.0,0},{5.0,-8.0,0}, {6.0,-8.0,0}, {7.0,-8.0,0}, {8.0,-8.0,0},{9.0,-8.0,0}, {10.0,-8.0,0},

{-3.0,-7.0,0}, {1.0,-7.0,0},{3.0,-7.0,0}, {7.0,-7.0,0}, //line 2
{-6.0,-6.0,0}, {-3.0,-6.0,0}, {1.0,-6.0,0}, {3.0,-6.0,0}, {7.0,-6.0,0}, {10.0,-6.0,0}, //line 3

{-6.0,-5.0,0}, {-5.0,-5.0,0}, {-4.0,-5.0,0}, {-3.0,-5.0,0}, {-2.0,-5.0,0}, {-1.0,-5.0,0}, {0,-5.0,0}, {1.0,-5.0,0}, //line4
{ 2.0,-5.0,0},{3.0,-5.0,0}, {4.0,-5.0,0}, {5.0,-5.0,0}, {6.0,-5.0,0}, {7.0,-5,0}, {8.0,-5.0,0}, {9.0,-5.0,0}, {10.0,-5.0,0},

{-6.0,-4.0,0}, {-3.0,-4.0,0}, {-1.0,-4.0,0}, {5.0,-4.0,0}, {7.0,-4.0,0}, {10.0,-4.0,0},//line5
{-6.0,-3.0,0}, {-5.0,-3.0,0}, {-4.0,-3.0,0}, {-3.0,-3.0,0}, {-1.0,-3.0,0}, {0,-3.0,0}, {1.0,-3.0,0}, {3.0,-3.0,0}, {4.0,-3.0,0},//line6
{5.0,-3.0,0}, {7.0,-3.0,0}, {8.0,-3.0,0}, {9.0,-3.0,0}, {10.0,-3.0,0},

{-3.0,-2.0,0}, {7.0,-2.0,0}, {-3.0,-1.0,0}, {7.0,-1.0,0}, {-3.0,0,0}, {7.0,0,0}, {-3.0,1.0,0}, {7.0,1.0,0},//line7-line10
{-3.0,2.0,0}, {7.0,2.0,0}, {-3.0,4.0,0}, {7.0,4.0,0},  {-3.0,3.0,0}, {7.0,3.0,0},//line11-line13

{-6.0,5.0,0}, {-5.0,5.0,0}, {-4.0,5.0,0}, {-3.0,5.0,0},{-2.0,5.0,0}, {-1.0,5.0,0},//line 14
{0.0,5.0,0}, {1.0,5.0,0}, {3.0,5.0,0}, {4.0,5,0}, {5,5,0}, {6.0,5,0}, {7,5,0}, {8,5,0}, {9,5,0}, {10,5,0},

{-6.0,6.0,0}, {-3.0,6.0,0}, {1.0,6.0,0}, {3.0,6.0,0}, {7.0,6.0,0}, {10.0,6.0,0}, //line 15

{-5.0,7.0,0}, {-3.0,7.0,0}, {-2.0,7.0,0}, {-1.0,7.0,0}, {0,7.0,0}, {1,7,0}, {3.0,7.0,0}, {4.0,7.0,0}, {5.0,7.0,0}, {6.0,7.0,0}, //line 16
{7.0,7.0,0}, {9.0,7.0,0},

{-5.0,8.0,0}, {-3.0,8.0,0}, {-1.0,8.0,0}, {9.0,8.0,0}, {5.0,8.0,0}, {7.0,8.0,0}, //line 17
{-6.0,9.0,0}, {-5.0,9.0,0}, {-4.0,9.0,0}, {-3.0,9.0,0}, {-1.0,9.0,0}, {0,9.0,0}, {1.0,9.0,0}, {3.0,9.0,0}, {4.0,9.0,0},{5.0,9.0,0}, //line 18
{7.0,9.0,0}, {8.0,9.0,0}, {9.0,9.0,0}, {10.0,9.0,0},
{-6.0,10,0}, {1,10,0}, {3,10,0}, {10,10,0}, //line 19
{-6.0,11,0}, {-5.0,11,0}, {-4.0,11,0}, {-3.0,11,0}, {-2.0,11,0}, {-1.0,11,0}, {0,11,0}, {1.0,11,0}, {2,11,0}, //line 20
{3,11,0}, {4,11,0}, {5,11,0}, {6,11,0}, {7,11,0}, {8,11,0}, {9,11,0}, {10,11,0} };
//create the powerup
double golds[4][3] = { {-6.0,-7.0,0.0} ,{-6.0,7.0,0.0},{10.0,-7.0,0.0},{10.0,7.0,0.0}};
GLUquadricObj* quardratic{ nullptr };
//powerup thread
thread powerThread;
//pacman life
int pacmanlife = 3;
bool ifpower = false;
//create pacman and ghost
Pacman pacman;
Ghost ghostR(2.0, 0.6, 0.5, 0);
Ghost ghostP(2.0, 0.6, 1.5,1);
Ghost ghostO(3.0, 0.6, 1.5,2);
Ghost ghostG(1.0, 0.6, 1.5,3);

// angle of rotation for the camera direction
int angle = 0.0; 
//the amount of eating coins
int coincount = 0, powerupcount = 0;
int direction = -1;


//initilize 
void init(void)
{   // set background color as black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    if (!quardratic)
        quardratic = gluNewQuadric();
}
//power thread
void power() {
    ifpower = true;
    this_thread::sleep_for(chrono::seconds(5));
    ifpower = false;
}
void powerthread() {
    powerThread = thread(&power);
}
//if eat powerup
void powerup(bool power) {
    if (power) {
        ghostR.runAway = true;
        ghostO.runAway = true;
        ghostG.runAway = true;
        ghostP.runAway = true;
    }
    if (!power && ghostR.runAway)
    {
        powerThread.join();

        ghostR.runAway = false;
        ghostO.runAway = false;
        ghostG.runAway = false;
        ghostP.runAway = false;
    }

}
//counting how many got eaten
void EatPowerup() {
    for (int i = 0; i < 4; ++i)
    {
        if (golds[i][2] == 0 && golds[i][0] == pacman.xPosition && golds[i][1] == pacman.zPosition) {
            golds[i][2] = 1;
            ++powerupcount;
            cout << "Eating power up: " << powerupcount << endl;
        }
    }

}
//whether in state of power up
bool Whetherpowerup(double& x,double& z) {

    for (int i = 0; i < 4; ++i)
    {
        if (golds[i][2] == 0 && golds[i][0] == x && golds[i][1] == z) {
               
            return true;
  
        }
    }
    return false;
}
//if lost the game
void LostGame() {
    if (pacmanlife == 0) {
        ghostR.ready = false;
        ghostG.ready = false;
        ghostP.ready = false;
        ghostO.ready = false;
        direction = -1;
     
        ghostG.ghostThread.join();
        ghostR.ghostThread.join();
        ghostP.ghostThread.join();
        ghostO.ghostThread.join();
        cout << "You have lost!" << endl;
        Sleep(3000);
        exit(0);
    }
}
//if win the game
void Win() {
    if (coincount == 152 && powerupcount == 4) 
    {

        ghostG.ready = false;
        ghostR.ready = false;
        ghostP.ready = false;
        ghostO.ready = false;
        direction = -1;

   

        ghostG.ghostThread.join();
        ghostO.ghostThread.join();
        ghostR.ghostThread.join();
        ghostP.ghostThread.join();
        cout << "You Win! " << endl;
        Sleep(3000);
        exit(0);
    }
}
//count how many coins got eaten
void EatCoins() {

    for (int i = 0; i < 152; ++i)
    {
        if (coins[i][2] == 0 && coins[i][0] == pacman.xPosition && coins[i][1] == pacman.zPosition)
        {
            coins[i][2] = 1;
            ++coincount;
            cout << "Eating coin count: " << coincount << endl;
        }
    }


  



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
            glutSolidSphere(0.2, 20, 20);//coins radius and basic conditions
            glPopMatrix();
        }
    }
  

}
//draw powerup
void DrawPowerup(void) {

    EatPowerup();

    glColor3f(160.0f / 255.0f, 160.0f / 255.0f, 30.0f / 255.0f); //Define the color for powers.
    for (int i = 0; i < 4; i++)
    {
        
        if (golds[i][2] == 0)  
        {
            glPushMatrix();
            glTranslatef(golds[i][0], 0, golds[i][1]);
            glRotatef(-90, 1, 0, 0);
            GLUquadricObj* objDisk = gluNewQuadric();
            gluDisk(objDisk, 0.01, 0.35, 40, 40);//power up basic conditions
            glPopMatrix();

        }
    }

}
//update the pacman direction   
void update(void) {
    Sleep(250);
    switch (direction)
    {
    case -1:
        break;
    case 0:
        pacman.move(0);
        glutPostRedisplay();
        break;
    case 1:
        pacman.move(1);
        glutPostRedisplay();
        break;
    case 2:
        if (pacman.xPosition <= -7 && pacman.zPosition == 1)
        {
            pacman.xPosition = 10;
            pacman.zPosition = 1;
        }
        else
        {
            pacman.move(2);
        }
        glutPostRedisplay();

        break;
    case 3:
        if (pacman.xPosition >= 10 && pacman.zPosition == 1)
        {
            pacman.xPosition = -7;
            pacman.zPosition = 1;
        }
        else
        {
            pacman.move(3);
    

        }

        glutPostRedisplay();

        break;
    }
}
//reshape scene
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);


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
        //start the ghost
    case 'g':
        ghostR.Init();
        ghostP.Init();
        ghostO.Init();
        ghostG.Init();
        glutPostRedisplay();
        break;
    case ESC:
        ghostG.ghostThread.join();
        ghostR.ghostThread.join();
        ghostP.ghostThread.join();
        ghostO.ghostThread.join();
        exit(0);
        
    }
}

//move the pacman
void PacmanMove(int key, int xx, int yy)
{

    switch (key)
    {
    case GLUT_KEY_UP:
        direction = 0;
        break;
    case GLUT_KEY_DOWN:
        direction = 1;
        break;
    case GLUT_KEY_LEFT:
        direction = 2;
        break;
    case GLUT_KEY_RIGHT:
        direction = 3;
        break;
    }
}

//draw maze
void Maze(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    //core maze
    glPushMatrix();
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0.0, 0.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, 2.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.0, 4.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 0.0, 2.0);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 0.0, -2.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -4.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, 0.0, -4.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0, 0.0, -2.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0, 0.0,2.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    //outer maze
    glPushMatrix();
    glTranslatef(2.0, 0.0, 4.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, 0.0, 8.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, 0.0, -6.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 8.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 4.0f, 32, 32);
    glPopMatrix();

    //sides
    //left top side
    glPushMatrix();
    glTranslatef(-7.0, 0.0, -2.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 7.0f, 32, 32);
    glPopMatrix();

    //top
    glPushMatrix();
    glTranslatef(-7.0, 0.0, -9.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 18.0f, 32, 32);
    glPopMatrix();
    //bottom
    glPushMatrix();
    glTranslatef(-7.0, 0.0, 12.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 18.0f, 32, 32);
    glPopMatrix();

    //left bottom side
    glPushMatrix();
    glTranslatef(-7.0, 0.0, 12.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 8.0f, 32, 32);
    glPopMatrix();

    //right top side
    glPushMatrix();
    glTranslatef(11.0, 0.0, -2.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 7.0f, 32, 32);
    glPopMatrix();

    //right bottom side
    glPushMatrix();
    glTranslatef(11.0, 0.0, 12.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 8.0f, 32, 32);
    glPopMatrix();
    // left top cuved side
    glPushMatrix();
    glTranslatef(-4.0, 0.0, -2.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.0, 0.0, 0.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();
    // left bottom cuved side
    glPushMatrix();
    glTranslatef(-4.0, 0.0, 2.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, 0.0, 2.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, 0.0, 4.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();


    //righ bottom curved side
    glPushMatrix();
    glTranslatef(8.0, 0.0, 2.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 0.0, 2.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 0.0, 4.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();

    //right top  curved side
    glPushMatrix();
    glTranslatef(8.0, 0.0, -2.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 0.0, 0.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(11.0, 0.0, 0.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 3.0f, 32, 32);
    glPopMatrix();


    //top small part
    //left
    //line 1
    glPushMatrix();
    glTranslatef(-5.0, 0.0, -4.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //square 1
    glPushMatrix();
    glTranslatef(-5.0, 0.0, -6.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0, 0.0, -6.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, 0.0, -7.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, 0.0, -7.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //square 2
    glPushMatrix();
    glTranslatef(-2.0, 0.0, -6.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, 0.0, -6.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -7.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, -7.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //right
    //line 2
    glPushMatrix();
    glTranslatef(8.0, 0.0, -4.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //square 3

    glPushMatrix();
    glTranslatef(4.0, 0.0, -6.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0, 0.0, -6.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0, 0.0, -7.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.0, 0.0, -7.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //square 4
    glPushMatrix();
    glTranslatef(8.0, 0.0, -6.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 0.0, -6.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.0, 0.0, -7.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.0, 0.0, -7.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //bottom small part
    //left bottom
    glPushMatrix();
    glTranslatef(0.0, 0.0,6.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();
    // like 7 shape
    glPushMatrix();
    glTranslatef(-4.0, 0.0, 6.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.0, 0.0, 6.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0, 0.0, 8.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    //like t shape
    glPushMatrix();
    glTranslatef(-2.0, 0.0, 10.0);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 10.0);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 5.0f, 32, 32);
    glPopMatrix();

    //right bottom parts
    glPushMatrix();
    glTranslatef(4.0, 0.0, 6.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    // like 7 shape
    glPushMatrix();
    glTranslatef(8.0, 0.0, 6.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 1.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.0, 0.0, 6.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.0, 0.0, 8.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f,1.0f, 32, 32);
    glPopMatrix();

    //like t shape
    glPushMatrix();
    glTranslatef(6.0, 0.0, 8.0);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 2.0f, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.0, 0.0, 10.0);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(quardratic, 0.04f, 0.04f, 5.0f, 32, 32);
    glPopMatrix();


    

 


 

    //glutSwapBuffers();
}
//render the scene
void Display(void)
{

    //set diplay
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set light and color material
    GLfloat light_diffuse[] = { 2.0, 2.0, 2.0, 1.0 };
    GLfloat light_position[] = { 15.0, 15.0, 15.0, 0.0 };

    //set light
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //set camera
    gluLookAt(
        0.0, 13.5, 8.0,
        0.0, -1, 0.0,
        0.0, 0.0, -1.0);

    glPushMatrix();
    glTranslatef(0.0, 1.0, -1.0);
    glRotatef((GLfloat)angle, 0.0, 1.0, 0.0);//set rotate point
    //draw maze
    Maze();
    //position of pacman
    pair<double, double> pacmanpostion(pacman.xPosition, pacman.zPosition);
    double x = pacmanpostion.first;
    double z = pacmanpostion.second;
    //four position of ghost
    pair<double, double> redghostpos(ghostR.next_X, ghostR.next_Z);
    pair<double, double> pinkghostpos(ghostP.next_X, ghostP.next_Z);
    pair<double, double> greenghostpos(ghostG.next_X, ghostG.next_Z);
    pair<double, double> orangeghostpos(ghostO.next_X, ghostO.next_Z);
    //ghost move path
    if (ghostR.ready) {
        ghostR.MovePath(redghostpos, pacmanpostion);
    }
    if (ghostG.ready) {
        ghostG.MovePath(greenghostpos, pacmanpostion);
    }
    if (ghostO.ready) {
        ghostO.MovePath(orangeghostpos, pacmanpostion);
    }
    if (ghostP.ready) {
        ghostP.MovePath(pinkghostpos, pacmanpostion);
    }

    if (Whetherpowerup(x, z)) {
        powerthread();
    }
    //put the powerup
    DrawPowerup();
    //the effect of power up
    if (ifpower&&(!ghostR.runAway || !ghostG.runAway || !ghostO.runAway || !ghostP.runAway)) {
        ghostR.runAway = true;
        ghostO.runAway = true;
        ghostG.runAway = true;
        ghostP.runAway = true;
    }
    if (!ifpower && (ghostR.runAway|| ghostG.runAway || ghostO.runAway || ghostP.runAway))// && ghostG.runAway && ghostO.runAway && ghostP.runAway
    {
        powerThread.join();

       ghostR.runAway = false;
       ghostO.runAway = false;
       ghostG.runAway = false;
       ghostP.runAway = false;
    }
    //count powerup
    EatPowerup();
    //PACMAN USE LIFE
    if (ghostG.Ifcatch(x,z)|| ghostR.Ifcatch(x, z)||ghostP.Ifcatch(x, z)||ghostO.Ifcatch(x, z)) {
       
        pacmanlife--;
        direction = -1;
        pacman.xPosition = 2.0;
        pacman.zPosition = 7.0;

        ghostG.ghostThread.join();
        ghostR.ghostThread.join();
        ghostO.ghostThread.join();
        ghostP.ghostThread.join();

       

        ghostG.Init();
        ghostR.Init();
        ghostO.Init();
        ghostP.Init();
    }
    else{
        if (ghostR.killed(x,z))
        {
            ghostR.ghostThread.join();
            ghostR.Init();
        }
        if (ghostO.killed(x, z))
        {
            ghostO.ghostThread.join();
            ghostO.Init();
        }
        if (ghostG.killed(x, z))
        {
            ghostG.ghostThread.join();
            ghostG.Init();
        }
        if (ghostP.killed(x, z))
        {
            ghostP.ghostThread.join();
            ghostP.Init();
        }

    }
    //determine whether lost or win
    LostGame();
    Win();
    //draw pacman and count eating coins
    pacman.drawPacman();
    EatCoins();
    //put the coins
    DrawCoins();


    //draw ghost
    ghostG.drawGhostGreen();
    ghostO.drawGhostOrange();
    ghostP.drawGhostPink();
    ghostR.drawGhostRed();





    glPopMatrix();
    glutSwapBuffers();
 



}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(910, 910);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pacman");
    glEnable(GL_DEPTH_TEST);

    init();
 
    glutDisplayFunc(Display);//display callback
    glutReshapeFunc(reshape);//window reshape callback
    glutIdleFunc(update);//update direction
    glutSpecialFunc(PacmanMove);//change the direction by keyboard
    glutKeyboardFunc(keyboard);//keyboard callback
  
    
    glutMainLoop();
    return 0;
}