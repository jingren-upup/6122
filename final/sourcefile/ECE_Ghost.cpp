/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: 2020/11/26
Description:
This program is the implementation file of the header file ECE_Ghost. It contains four
functions to draw the ghost in red green pink and orange color in the coordinate system.
and function to determine which is the shortest way and how should the ghost move.
*/



#include"ECE_Ghost.h"

using namespace std;
//set ghost value
Ghost::Ghost(double x,double y ,double z,int seq)
{
    //constructor
 
    this->Yposition = y;
    this->start_X = x;
    this->start_Z = z;

    this->next_X = x;
    this->next_Z = z;


    this->seq = seq;
   
}
//draw four ghost
void Ghost::drawGhostRed() {
    if (this->runAway)
    {
        glColor3f(1.0, 1.0, 1.0);
    }else
    {
        glColor3f(1.0, 0.0, 0.0); // red
    }

 
    glPushMatrix();
    glTranslatef(next_X, Yposition, next_Z);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X, Yposition-0.5, next_Z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.4f, 0.25f, 0.5f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(next_X -0.1, Yposition+0.1, next_Z +0.1);
    glutSolidSphere(0.17, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X+0.1, Yposition+0.1, next_Z +0.1);
    glutSolidSphere(0.17, 10, 10); // right eye
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0); //black pupil

    glPushMatrix();
    glTranslatef(next_X -0.12, Yposition+0.12, next_Z +0.12);
    glutSolidSphere(0.14, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X +0.12, Yposition+0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10); // right eye
    glPopMatrix();


}
void Ghost::drawGhostPink()
{
    if (this->runAway)
    {
        glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
        glColor3f(1.0, 0, 1.0); // pink
    }

    glPushMatrix();
    glTranslatef(next_X, Yposition, next_Z);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X, Yposition - 0.5, next_Z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.4f, 0.25f, 0.5f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(next_X - 0.1, Yposition + 0.1, next_Z + 0.1);
    glutSolidSphere(0.17, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X + 0.1, Yposition + 0.1, next_Z + 0.1);
    glutSolidSphere(0.17, 10, 10); // right eye
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0); //black pupil

    glPushMatrix();
    glTranslatef(next_X - 0.12, Yposition + 0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X + 0.12, Yposition + 0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10); // right eye
    glPopMatrix();

}
void Ghost::drawGhostGreen()
{
    if (this->runAway)
    {
        glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
        glColor3f(0.0, 1.0, 0.0); // green
    }
   

    glPushMatrix();
    glTranslatef(next_X, Yposition, next_Z);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X, Yposition - 0.5, next_Z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.4f, 0.25f, 0.5f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(next_X - 0.1, Yposition + 0.1, next_Z + 0.1);
    glutSolidSphere(0.17, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X + 0.1, Yposition + 0.1, next_Z + 0.1);
    glutSolidSphere(0.17, 10, 10); // right eye
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0); //black pupil

    glPushMatrix();
    glTranslatef(next_X - 0.12, Yposition + 0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X + 0.12, Yposition + 0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10); // right eye
    glPopMatrix();


}
void Ghost::drawGhostOrange()
{

    if (this->runAway)
    {
        glColor3f(1.0, 1.0, 1.0);
    }
    else
    {
        glColor3f(1, 0.5, 0); // organge
    }
  
  

    glPushMatrix();
    glTranslatef(next_X, Yposition, next_Z);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X, Yposition - 0.5, next_Z);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic, 0.4f, 0.25f, 0.5f, 32, 32);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0); // eyes are white

    glPushMatrix();
    glTranslatef(next_X - 0.1, Yposition + 0.1, next_Z + 0.1);
    glutSolidSphere(0.17, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X + 0.1, Yposition + 0.1, next_Z + 0.1);
    glutSolidSphere(0.17, 10, 10); // right eye
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0); //black pupil

    glPushMatrix();
    glTranslatef(next_X - 0.12, Yposition + 0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10);// left eye
    glPopMatrix();

    glPushMatrix();
    glTranslatef(next_X + 0.12, Yposition + 0.12, next_Z + 0.12);
    glutSolidSphere(0.14, 10, 10); // right eye
    glPopMatrix();

}









//chose which way should go
void Ghost::MovePath(const pair<double, double>& ghostPosition,const pair<double, double>& pmPosition)
{
    pair<double, double> awaypath(2-pmPosition.first,1-pmPosition.second);//create away point and used when powerup
    if (Ifcatch(pmPosition.first, pmPosition.second)) {//if catch , wait for restart
        return;
    }
    if (this->runAway)//if powerup,use the runaway point
    {
        switch (shortestpath(ghostPosition, awaypath))
        {
        case 0:
            this->next_Z -= 1;
            break;
        case 1:
            this->next_Z += 1;
            break;
        case 2:
            this->next_X -= 1;
            break;
        case 3:
            this->next_X += 1;
            break;
        }
    }
    else//normal occasion
    {
        switch (shortestpath(ghostPosition, pmPosition))
        {
        case 0:
            this->next_Z -= 1;
            break;
        case 1:
            this->next_Z += 1;
            break;
        case 2:
            this->next_X -= 1;
            break;
        case 3:
            this->next_X += 1;
            break;
        }
    }
    //if pass tunnel
    if (this->next_X == 12 && this->next_Z==1.0)
    {
        this->next_X = -7.0;
    }
    if (this->next_X == -8 && this->next_Z == 1.0)
    {
        this->next_X = 11;
    }
    


}
//using DFS to find shortest way
int Ghost::shortestpath(const pair<double, double>& start, const pair<double, double>& end)
{
    struct note que[500];
    int head = 0, tail = 1;
    double rt[420][3];
    double x = start.first;
    double z = start.second;
    double dx[4] = { 0.0,0.0,-1.0,1.0};//offset
    double dz[4] = { -1.0,1.0,0.0,0.0 };

    for (int i = 0; i < 418; ++i)
    {
        for (int j = 0; j < 3; j++)
        {
            rt[i][j] = this->routes[i][j];//transfer data into it
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        double txx = x + dx[i];
        double tzz = z + dz[i];
        if (getroute(txx, tzz, rt) == 0.0 && txx == end.first && tzz == end.second)//if next is destiney
        {
            return i;
        }
    }

    //default value
    que[head].x = x;
    que[head].z = z;
    que[head].f = -1;
    que[head].s = 0;
    que[head].pos = -1;
    setRoute(x, z, rt,2);

    while (head < tail)//if not empty queue
    {
        for (int i = 0; i < 4; ++i)
        {
            double tx = que[head].x + dx[i];
            double tz = que[head].z + dz[i];//next postition
            //if pass tunnel
            if (tx == -8)
            {
                tx = 11;
            }
            if (tx == 12)
            {
                tx = -7;
            }
            if (getroute(tx, tz, rt) == 0)//if find
            {
                setRoute(tx, tz, rt, 3);
                que[tail].x = tx;
                que[tail].z = tz;
                que[tail].f = head;//record father
                que[tail].s = que[head].s + 1;// step
                que[tail].pos = i;
                ++tail;//expand length
            }
            if (tx == end.first && tz == end.second)
            {
               
                int t = que[tail - 1].f;
     
                /*if (t <= 0)
                {
                    return que[t].pos;
                }*/
                while (que[t].f > 0)//to find the next step which is the shortest way
                {
                    int temp = que[t].f;
                    t = temp;
                 
                }
                return que[t].pos;
            }
        }
        ++head;//output queue
    }
    
}
//find the route of ghost
double Ghost::getroute(double x, double z, double way[418][3])
{
    double data;
    for (int i = 0; i < 420; ++i)
    {
        if (way[i][0] == x && way[i][1] == z)
        {
            data = way[i][2];
            return data;
        }
    }
}
//set the route of ghost
void Ghost::setRoute(double x, double z, double way[418][3], double data)
{
    for (int i = 0; i < 420; ++i)
    {
        if (way[i][0] == x && way[i][1] == z)
        {
            way[i][2] = data;
        }
    }
}
//whether catch the pacman
bool Ghost::Ifcatch(double pmx, double pmz) {

    if (this->next_X == pmx && this->next_Z == pmz&& !runAway ) //
    {
        return true;
    }
    return false;
}
//ghost start from the home
void Ghost::startmove(int i)
{
    if (i==0)
    {
        this_thread::sleep_for(chrono::seconds(1));
    }
    this_thread::sleep_for(chrono::seconds(i*2));
  
    this->next_X = 2.0;
    this->next_Z = -1.0;
    this->ready = true;
}
//ghost is killed
bool Ghost::killed(double x, double z)
{
    if (this->next_X == x && this->next_Z == z && runAway)
    {
        return true;
    }
    return false;
}
//killed and reset the ghost
void Ghost::reset(int i){
    this_thread::sleep_for(chrono::seconds(5));
   // if (i == 0 || i == 1) {
        this->next_X = 2.0;
        this->next_Z = -1.0;
    this->ready = true;
}
//init the ghost and create thread
void Ghost::Init() {
    this->next_X = this->start_X;
    this->next_Z = this->start_Z;
    this->ready = false;
    if (runAway)
    {
        ghostThread = thread(&Ghost::reset, this,seq);
    }
    else
    {
        ghostThread = thread(&Ghost::startmove, this, seq);
    }

}


