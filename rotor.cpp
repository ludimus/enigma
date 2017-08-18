#include <iostream>
#include <string>
#include "rotor.h"
using namespace std;

rotor::rotor()
{
    rotortype=0;
    rotorring=0;
    rotorpos=0;
}

rotor::rotor(int t,int r,int p)
{
    rotortype=t;
    rotorring=r;
    rotorpos=p;
}

void rotor::settype(int rt)
{
    rotortype=rt-1;
}

void rotor::setpos(int rp)
{
    rotorpos=rp-1;
}

void rotor::setpos(char rp)
{
    rotorpos=(int)rp-65;
}

void rotor::setring(int rp)
{
    rotorring=rp-1;
}

string rotor::gettype()
{
    string ringtype[10]={"I","II","III","IV","V","VI","VII","VIII","Beta","Gamma"};
    return ringtype[rotortype];
}

char rotor::getpos()
{
    return((char)(rotorpos+65));

}

char rotor::getring()
{
    return((char)(rotorpos+65));
}



bool rotor::rotate()
{

}


char rotor::encode(char s)
{
}

char rotor::decode(char s)
{
}


