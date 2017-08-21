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
    ringsetting=0;
}

//
// rotor constructor
//

rotor::rotor(int type, int ring){
    init(type,ring);
}



void rotor::init(int type,int ring)
{
//  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
//  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 

    int turnover[8]= {17,5,22,10,0,0,0,0};
   
    
    int all_wires[8][26]={{4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9},
                          {0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4},
                          {1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14},
                          {4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1},
                          {21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10},
                          {9,15,6,21,14,20,12,5,24,16,1,4,13,7,25,17,3,10,0,18,23,11,8,2,19,22},
                          {13,25,9,7,6,17,2,23,12,24,18,22,1,14,20,5,0,8,21,11,15,4,10,16,3,19},
                          {5,10,16,7,19,11,23,14,2,1,9,18,15,3,25,17,0,12,4,22,13,8,20,24,6,21}
                         };
    
    // make reverse wires matrix
    int all_wires_reverse[8][26];
    for (int r=0;r<8;r++)
       for(int c=0;c<26;c++){
           int k=0;
           while (all_wires[r][k]!=c) k++;
           all_wires_reverse[r][c]=k;
       }
    
    // initialize rotor, ring and wires
    rotortype=type;
    rotorpos=0;
    ringpos=ring;
    ringsetting=ring;
    notchpos=turnover[type];

    //set wiring and reverse wiring for rotortype
    
    for (int w=0;w<26;w++){
         wires[w]=all_wires[type][w];
         wiresback[w]=all_wires_reverse[type][w];
    }
    //turn rotor in 0-position
    while(ringpos!=0) step();
}

//Getters

int rotor::getrotortype(){ return rotortype;}
int rotor::getrotorpos(){ return rotorpos;}
int rotor::getringpos(){ return ringpos;}
int rotor::getringsetting() { return ringsetting;}


// Rotor operations

void rotor::step()
{
    rotorpos=(rotorpos+1)%26;
    ringpos=(ringpos+1)%26;
}


void rotor::setpos(int p){
    while(ringpos!=p) step();
}


int rotor::encode(int c) 
{
    c=(c+rotorpos)%26;      // adjust entry to rotorposition
    c=wires[c];             // go through the wires
    c=c-rotorpos;           // adjust exit to rotorposition;
    if(c<0)c+=26;
    return (c);                    
}

int rotor::reverse(int c)
{
    c=(c+rotorpos)%26;      // adjust entry to rotorposition
    c=wiresback[c];         // go through the wiresback
    c=c-rotorpos;           // adjust exit to rotorposition;
    if(c<0)c+=26;
    return (c);             
}

// Check notch functions
bool rotor::over_notch() { 
    
    bool notched=false;
    
    //check if ring is over the notch
    notched=(ringpos==notchpos);
        
    //check for ringtype VI,VII,VIII the second notch from M->N
    if ((notched==false)&&(rotortype>4)&&(ringpos==13))
        notched=true;
    
    return notched;
}

bool rotor::on_notch() {
    bool notched=false;
    
    //check if ring is on the notch
    notched=((ringpos+1)%26==notchpos);
        
    //check for ringtype VI,VII,VIII onthe second notch from M->N
    if ((notched==false)&&(rotortype>4)&&((ringpos+1)%26==13))
        notched=true;
    
    return notched;
}
