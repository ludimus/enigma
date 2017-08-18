#include <iostream>
#include <string>
#include "reflector.h"
using namespace std;



reflector::reflector()
{
    setwires(0);
}


void reflector::setwires(int rt){

// todo set reflectors 1-3 (not used now)
   char
   box[4][26]={{'Y','R','U','H','Q','S','L','D','P','X','N','G','O','K','M','I','E','B','F','Z','C','W','V','J','A','T'},
               {'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'},
               {'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'},
               {'E','S','O','V','P','Z','J','A','Y','Q','U','I','R','H','X','L','N','F','T','G','K','D','C','M','W','B'},
              };
   for (int w=0;w<26;w++)
       wires[w]=box[rt][w];
    
}


char reflector::reflect(char s)
{
    return (wires[(int)(s-65)]);
}


