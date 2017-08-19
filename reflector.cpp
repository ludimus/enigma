#include <iostream>
#include <string>
#include "reflector.h"
using namespace std;



reflector::reflector(int n)
{
    setwires(n);
}


void reflector::setwires(int rt){

// todo set reflectors 1-3 (not used now)
   int  all_reflectors[4][26]={{24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19},
                               {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
                               {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
                               {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25},
                              };
   for (int w=0;w<26;w++)
       wires[w]=all_reflectors[rt][w];
    
}


int reflector::reflect(int c)
{
    return (wires[c]);
}


