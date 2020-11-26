/*
Author: Jingren Wang
Class: ECE6122
Last Date Modified: Sept. 7th,2020
Description:
The program is to calculates the number of times the beam is reflected
in a "white cell".Top surface of x from -0.01 to 0.01 can be ignored,
allowing the light to exit the ellipse. the beam starts at the point (0.0,10.1)
and hits at (1.4,-9.6). The solution need to calculate the number of times
the beam can exit the ellipse, and output result to a text file called
output4.txt.
*/

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;


double tangent_slope(pair<double,double>a){
    //calculate the slope of the tangent line
    double  k;//k means slope
    k = -4* a.first/a.second;
    return k;
}

double reflection_slope(pair<double,double>a, double k0){
    //calculate the slope of the reflection ray
    double slope,k1,k2;
    k1 = k0;
    k2 = tangent_slope(a);//use return value
    slope = (2*k2 - k1 * (1 - k2 * k2))/ (1 - k2 * k2 + 2*k1*k2);//relation of several slope

    return slope;
}



int main()
{
    //initialize
    int step = 1;


    double k0 = -(10.1+9.6)/1.4;//original line slope


    double c,k_new,x,y;//c is parameter in kx+c =y,k_new means new slope
    typedef pair<double,double> point;


    point from(0.0,10.1);
    point to(1.4,-9.6);


    tangent_slope(to);

    k_new = reflection_slope(to,k0);//return calculated slope value


    while(1){

       //set x y and c with value
        x = to.first;
        y = to.second;
        c = y - k_new * x;
        // end point become start point
        from.first = x;
        from.second = y;
        //new point is set by a formulae between ellipse and line
        to.first = (-2 * k_new*c) / (k_new*k_new + 4)- x;
        to.second = c + k_new * to.first;

        if(to.second> 0 && abs(to.first)<0.01){// if it can exit, break the loop
            break;
        }

        k_new = reflection_slope(to,k_new);//swap slope

        step++;//number counted


    }
//ofs processing
    cout<<step;

    ofstream ofs("output4.txt", ofstream::out);
    ofs << step;
    ofs.close();

    return step;

}