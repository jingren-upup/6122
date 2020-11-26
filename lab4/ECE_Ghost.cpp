/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/10/27
Description:
This function is to draw ghosts and paint colors.
*/


#include"ECE_Ghost.h"



void Ghost::drawGhostRed() {


    glColor3f(1.0, 0.0, 0.0); // red
    glPushMatrix();
    glTranslatef(0.4, 0.12, 0.15);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, 0.02, 0.15);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.06f, 0.06f, 0.12f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(0.38, 0.12, 0.13);
    glutSolidSphere(0.01, 10, 10); // left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42, 0.12, 0.13);
    glutSolidSphere(0.01, 10, 10); // right eye
    glPopMatrix();


}

void Ghost::drawGhostPink()
{
    glColor3f(1.0, 0, 1.0); // pink
    glPushMatrix();
    glTranslatef(0.4, 0.12, 0.3);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, 0.02, 0.3);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.06f, 0.06f, 0.12f, 32, 32);
    glPopMatrix();


    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(0.38, 0.12, 0.3);
    glutSolidSphere(0.01, 10, 10); // left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.42, 0.12, 0.3);
    glutSolidSphere(0.01, 10, 10); // right eye
    glPopMatrix();

}


void Ghost::drawGhostGreen()
{
    glColor3f(0.0, 1.0, 0.0); // green
    glPushMatrix();
    glTranslatef(0.2, 0.12, 0.3);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 0.02, 0.3);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.06f, 0.06f, 0.12f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(0.18, 0.12, 0.3);
    glutSolidSphere(0.01, 10, 10); // left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.22, 0.12, 0.3);
    glutSolidSphere(0.01, 10, 10); // right eye
    glPopMatrix();

}

void Ghost::drawGhostOrange()
{
    glColor3f(1, 0.5, 0); // organge
    glPushMatrix();
    glTranslatef(0.6, 0.12, 0.3);
    glutSolidSphere(0.06, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6, 0.02, 0.3);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.06f, 0.06f, 0.12f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(0.58, 0.12, 0.3);
    glutSolidSphere(0.01, 10, 10); // left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.62, 0.12, 0.3);
    glutSolidSphere(0.01, 10, 10); // right eye
    glPopMatrix();

}

