#include <iostream>
#include "reflector.hpp"

using namespace std;

//Reflector details: https://en.wikipedia.org/wiki/Enigma_rotor_details
//


// Constructors:
// default constructor defaults to reflector "B"
//
reflector::reflector()
{
    init(1);
}


// Constructor to set reflectors for Enigma M3 models:
// 0=reflector A 1=reflector B 2=reflector C
//
reflector::reflector(int n)
{
    init(n);
}


//
// init function set type and wires for this reflector
//
void reflector::init(int n)
{
    reflectortype=n;
    
    int  all_reflectors[3][26]={{4,9,12,25,0,11,24,23,21,1,22,5,2,17,16,20,14,13,19,18,15,8,10,7,6,3},    //A
                                 {24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19},   //B
                                 {5,21,15,9,8,0,14,24,4,3,17,25,23,22,6,2,19,10,20,16,18,1,13,12,7,11},   //C       
                               };
    if((n>=0)&&(n<=2))
        for (int w=0;w<26;w++)
            wires[w]=all_reflectors[n][w];
    else
        cout<<"Invalid reflector type: "<<(char)(n+65)<<endl;
}

//
//Getter for reflectortype
//
int reflector::gettype(){ return reflectortype;}


//
// reflect function for scrambling:
// Example: A(0) would return Y(24) for reflector B
//
int reflector::reflect(int c)
{
    return (wires[c]);
}


