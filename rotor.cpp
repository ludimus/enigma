#include <iostream>
#include <string>
#include "rotor.h"
using namespace std;

//
// Default constructor (should not be used)
//

rotor::rotor()
{
    rotortype=0;
    rotorpos=0;
    ringpos=0;
    notchpos=0;
}

//
// rotor constructor
//
rotor::rotor(int type,int rotor,int ring)
{

    int turnover[5]={17,5,22,10,0};
    int all_wires[5][26]={{4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9},
                          {0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4},
                          {1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14},
                          {4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1},
                          {21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10}
                         };
    
    // make reverse wires
    int all_wires_reverse[5][26];
    for (int r=0;r<5;r++)
       for(int c=0;c<26;c++){
           int k=0;
           while (all_wires[r][k]!=c) k++;
           all_wires_reverse[r][c]=k;
       }
    
    // initialize rotor, ring and wires
    rotortype=type;
    rotorpos=rotor;
    ringpos=(rotorpos+ring)%26;
    rotorpos-=ring;
    if (rotorpos<0) rotorpos+=26;     
    
    notchpos=turnover[type];

    //set wiring and reverse wiring for rotortype
    
    for (int w=0;w<26;w++){
         wires[w]=all_wires[type][w];
         wiresback[w]=all_wires_reverse[type][w];
    }
}

//Getters

string rotor::getrotortype()
{
    string ringtype[5]={"I","II","III","IV","V"};
    return ringtype[rotortype];
}

int rotor::getrotorpos(){ return rotorpos;}

int rotor::getringpos(){ return ringpos;}


// Rotor operations

void rotor::step()
{
    rotorpos=(rotorpos+1)%26;
    ringpos=(ringpos+1)%26;
    cout<<"rotating..."<<rotorpos<<" " <<ringpos<<endl;
}


int rotor::encode(int c) 
{
    cout<<"Incoming: "<<c<<endl;
    c=(c+rotorpos)%26;      //adjust entry to rotorposition
    cout<< "Adjusted to rotor: "<<c<<endl;
    c=wires[c];        // go through the wires
    cout<<"Wires: "<<c<<endl;
    c=c-rotorpos;          // adjust exit to rotorposition;
    if(c<0)c+=26;
    cout<<"Outgoing: "<<c<<endl;
    return (c);             // return Character



}

int rotor::reverse(int c)
{
    cout<<"Reverse Incoming: "<<c<<endl;
    c=(c+rotorpos)%26;      //adjust entry to rotorposition
    cout<< "Reverse Adjusted to rotor: "<<c<<endl;
    c=wiresback[c];        // go through the wiresback
    cout<<"Reverse Wires: "<<c<<endl;
    c=c-rotorpos;          // adjust exit to rotorposition;
    if(c<0)c+=26;
    cout<<"Reverse Outgoing: "<<c<<endl;
    return (c);             // return Character
}

bool rotor::has_notched() { return (ringpos==notchpos);}

bool rotor::is_notched() { return (((ringpos+1)%26)==notchpos);}
