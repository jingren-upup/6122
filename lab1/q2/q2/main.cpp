/*
Author: jingren Wang
Class: ECE 6122
Last Date Modified: Sep 7, 2020
Description:
As for this program, it use a command-line argument with and determine if it is odd or even
in first method. In the main function, it parses the argv parameter amd output the sum in
a text file finally */

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

//judge the input if odd or even
//use Collatz sequence to process input and return a iterative result
long OddOrEven(long Num){
   if (Num % 2==0){
       return Num/2 ;
   }else if(Num == 1|| Num == 0 ){
       return Num;
   } else{
       return (3*Num)+ 1;
   }
}


// parse parameter and output
int main(int argc, char* argv[])
{
    // num is the variable changed by function. num1 is origin to judge if it is 1.
    unsigned long sum, num,num1;
    //transfer argv[1] into unsigned long type
    num = atol(argv[1]);
    num1 = num;
    sum = 0;
  if (num1 == 0){
      sum = 0;
  }else {
        do {
        sum += num;
        num = OddOrEven(num);
    }while (num != 1);
    if (num1 == 1 ){
        sum = num1;
    } else{
        sum++;
    }
    }

    //print result
    cout << "sum: "<< sum << endl;

    //ofs processing
    ofstream output;
    ofstream ofs("output2.txt", ofstream::out);
    ofs << sum;
    ofs.close();


}









