#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "enigmam3.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    
    enigmam3 E;
    
    
    int r1,r2,r3;
    
    char kl,kr,km,k4;
    char c1,c4;
    
    if(argc<2) {
        cout<< "usage: zygalski 213A, to generate sheet A for rotor position II I III"<<endl;
        exit(1);
    }
    
    r1=(int)(argv[1][0]-48);                        //read argument 1
    r2=(int)(argv[1][1]-48);
    r3=(int)(argv[1][2]-48);
    kl=argv[1][3];
    kl=toupper(kl);
    
    E.setRotor(1,r1-1,'A');                         //initialize rotors to type and ring A
    E.setRotor(2,r2-1,'A');
    E.setRotor(3,r3-1,'A');
    E.setRotorpos(1,kl);
    //E.display_enigma(); 
    
    for (km='A';km<='Z';km++){                      //set middle key
        for(kr='A';kr<='Z';kr++){                   //set right key
            bool isthisahole=false;    
            for(char c='A';c<='Z';c++){             // encrypt for all (a-z) first and 4th character
                E.setRotorpos(2,km);                // set rotorpositions manually, do not use advance function
                E.setRotorpos(3,kr);                // sheets are calculated without notches
                c1=E.encode(c);
                k4=kr+3;
                if (k4 > 'Z')k4=k4-26;
                E.setRotorpos(3,k4);
                c4=E.encode(c);
                if(c1==c4)isthisahole=true;
            }                                       //end innerloop encrypt (a-z)
            if (isthisahole)cout<<"O";
            else cout<<".";
        }                                           //end right key
        cout<<endl;
        
    }                                               //end middle key
return 0;
}





