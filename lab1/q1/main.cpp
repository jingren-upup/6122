/*
Author: jingren Wang
Class: ECE 6122
Last Date Modified: Sep 6, 2020
Description:
As for this problem,the solution is about summing the primes below the given parameter by command line.
In main function,it will parse the input parameter in IsPrime Function and use a for loop to calculate the sum.
IsPrime is a function to determine whether the input is a prime number or not.
The program will output a sum to a text file called output1.txt finally.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

//to judge whether INum is a prime
// if it is,  return 1. If not, it will return 0.
bool IsPrime(long INum){
    if(INum == 1 || INum == 0){
        return false;
    }
    for(int i = 2; i <= INum / 2; ++i)
    {
        if(INum % i == 0)
        {return false;}
    }
    return true;
}


// transfer num to unsigned type, calculate the sum by using a for loop
int main(int argc, char* argv[])
{
    unsigned long sum, num;
//transfer
    num = atol(argv[1]);
    sum = 0;
//calculate
    for(int i = 2; i <= num;i++){
        if (IsPrime(i)){
          sum = sum + i;
        }
    }
    //print result
    cout << "sum: "<< sum << endl;
    //declare a variable named output
    ofstream output;
    //creat a file based on the given standard
    ofstream ofs("output1.txt", ofstream::out);
    ofs << sum;
    //close
    ofs.close();


}




