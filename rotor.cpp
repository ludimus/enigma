#include <iostream>
#include <string>
#include "rotor.h"
using namespace std;



rotor::rotor()
{
    rotortype=0;
    rotorring=0;
    rotorpos=0;
    setwires(0);
}

rotor::rotor(int t,int r,int p)
{
    rotortype=t-1;
    rotorring=r-1;
    rotorpos=p-1;
    setwires(t-1);
}


void rotor::setwires(int rt){

   char box[5][26]={{'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'},
                    {'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'},
                    {'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'},
                    {'E','S','O','V','P','Z','J','A','Y','Q','U','I','R','H','X','L','N','F','T','G','K','D','C','M','W','B'},
                    {'V','Z','B','R','G','I','T','Y','U','P','S','D','N','H','L','X','A','W','M','J','Q','O','F','E','C','K'}
                   };
   for (int w=0;w<26;w++)
       wires[w]=box[rt][w];
    
   char turnover[5]={'R','F','W','K','A'};
   nudge=turnover[rt];
    
   // make reverse wires
   char boxback[5][26];
   for (int r=0;r<5;r++)
       for(int c=0;c<26;c++){
           int k=0;
           while (box[r][k]!=(char(c+65))) k++;
           boxback[r][c]=((char)(k+65));
       }
    for(int wb=0;wb<26;wb++)
        wiresback[wb]=boxback[rt][wb];
}

string rotor:: getwires()
{
    string ret="";
    for (int i=0;i<26;i++)
        ret.push_back(wiresback[i]);
    return(ret);
}



void rotor::settype(int rt)
{
    rotortype=rt-1;
    setwires(rt-1);
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
    rotorpos-=rotorring;
    if (rotorpos<0) rotorpos+=26;     //The ring offsets the rotorpos
}

string rotor::gettype()
{
    string ringtype[5]={"I","II","III","IV","V"};
    return ringtype[rotortype];
}

char rotor::getpos()
{
    return((char)(rotorpos+65));

}

char rotor::getwindow()
{
    return((char)(((rotorpos+rotorring)%26)+65));
}
char rotor::getring()
{
    return((char)(rotorring+65));
}


void rotor::rotate()
{
    rotorpos=(rotorpos+1)%26;
}


char rotor::encode(char s)
{
    cout<<"Incoming: "<<s<<endl;
    char e=(s+rotorpos);      //adjust entry to rotorposition
    if (e>90) e-=26;
    cout<< "Adjusted to rotor: "<<e<<endl;
    e=wires[e-65];        // go through the wires
    cout<<"Wires: "<<e<<endl;
    e=e-rotorpos;          // adjust exit to rotorposition;
    if(e<65)e+=26;
    cout<<"Outgoing: "<<e<<endl;
    return (e);             // return Character



}

char rotor::reverse(char s)
{
    cout<<"Revere Incoming: "<<s<<endl;
    char e=(s+rotorpos);      //adjust entry to rotorposition
    if (e>90) e-=26;
    cout<< "Reverse Adjusted to rotor: "<<e<<endl;
    e=wiresback[e-65];        // go through the wires
    cout<<"Reverse Wires: "<<e<<endl;
    e=e-rotorpos;          // adjust exit to rotorposition;
    if(e<65)e+=26;
    cout<<"Reverse Outgoing: "<<e<<endl;
    return (e);             // return Character
}

bool rotor::is_nudged()
{
    bool ret=false;
    if (((int)nudge-65)==rotorpos)
        ret=true;
    return ret;    
}

bool rotor::check_doublestep(){
    bool ret=false;
    if (((int)nudge-65)==(rotorpos+1)%26)

        ret=true;

    return ret;
}
