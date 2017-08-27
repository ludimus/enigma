#include <iostream>
#include "rotor.hpp"
using namespace std;

// Rotor details can be found on: https://en.wikipedia.org/wiki/Enigma_rotor_details

//
// Default constructor, settings to Rotor I with ring setting A and notch Q->R
// 
rotor::rotor()
{
    rotortype=0;      
    rotorpos=0; 
    ringpos=0;
    notchpos=17;
    ringsetting=0;
}

//
// rotor constructor for rotor type and ringsetting
//
rotor::rotor(int type, int ring){
    init(type,ring);
}

//
// initialize rotor with correct type, positions and wiring
//
void rotor::init(int type,int ring)
{

    int turnover[8]= {17,5,22,10,0,0,0,0};
   
    
    int all_wires[8][26]={{4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9},            //I
                          {0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4},            //II
                          {1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14},            //III 
                          {4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1},            //IV
                          {21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10},            //V
                          {9,15,6,21,14,20,12,5,24,16,1,4,13,7,25,17,3,10,0,18,23,11,8,2,19,22},            //VI
                          {13,25,9,7,6,17,2,23,12,24,18,22,1,14,20,5,0,8,21,11,15,4,10,16,3,19},            //VII
                          {5,10,16,7,19,11,23,14,2,1,9,18,15,3,25,17,0,12,4,22,13,8,20,24,6,21}             //VIII
                         };
    //
    // to avoid searching reverse paths in the wiring during scrambling.
    // The reverse table is created, a simple lookup will do now.
    //
    int all_wires_reverse[8][26]={{20,22,24,6,0,3,5,15,21,25,1,4,2,10,12,19,7,23,18,11,17,8,13,16,14,9},    //I
                                  {0,9,15,2,25,22,17,11,5,1,3,10,14,19,24,20,16,6,4,13,7,23,12,8,21,18},    //II        
                                  {19,0,6,1,15,2,18,3,16,4,20,5,21,13,25,7,24,8,23,9,22,11,17,10,14,12},    //III
                                  {7,25,22,21,0,17,19,13,11,6,20,15,23,16,2,4,9,12,1,18,10,3,24,14,8,5},    //IV
                                  {16,2,24,11,23,22,4,13,5,19,25,14,18,12,21,9,20,3,10,6,8,0,17,15,7,1},    //V
                                  {18,10,23,16,11,7,2,13,22,0,17,21,6,12,4,1,9,15,19,24,5,3,25,20,8,14},    //VI
                                  {16,12,6,24,21,15,4,3,17,2,22,19,8,0,13,20,23,5,10,25,14,18,11,7,9,1},    //VII
                                  {16,9,8,13,18,0,24,3,21,10,1,5,17,20,7,12,2,15,11,4,22,25,19,6,23,14}     //VIII
                                 };
    
    // initialize rotor, set position of rotor, position of the ring and notch.
    
    rotortype=type;
    rotorpos=0;
    ringpos=ring;
    ringsetting=ring;
    notchpos=turnover[type];

    //set wiring for this rotortype
    
    for (int w=0;w<26;w++){
         wires[w]=all_wires[type][w];
         wiresback[w]=all_wires_reverse[type][w];
    }
    //turn rotor until the ring shows ringposition 0 (A) in the window.
    while(ringpos!=0) step();
}

//
//Getters, not sure this is correct programming...
//
int rotor::getrotortype(){ return rotortype;}
int rotor::getrotorpos(){ return rotorpos;}
int rotor::getringpos(){ return ringpos;}
int rotor::getringsetting() { return ringsetting;}

//
// Ring and rotor are attached together during installation, both take 1 step forward.
//
void rotor::step()
{
    rotorpos=(rotorpos+1)%26;
    ringpos=(ringpos+1)%26;
}

//
//setpos is used to rotate the rotor to the correct ringposition (like turning the wheel on the enigma)
//The ring shows the current position on the enigma
//
void rotor::setpos(int p){
    while(ringpos!=p) step();
}

//
//encode a character going forward through the rotor.
//
int rotor::encode(int c) 
{
    c=(c+rotorpos)%26;      // adjust entry to rotorposition
    c=wires[c];             // go through the wires
    c=c-rotorpos;           // adjust exit to rotorposition;
    if(c<0)c+=26;
    return (c);                    
}

//
//encode a character going backwards through the rotor.
//(signal coming back from the reflector)
//
int rotor::reverse(int c)
{
    c=(c+rotorpos)%26;      // adjust entry to rotorposition
    c=wiresback[c];         // go through the wiresback
    c=c-rotorpos;           // adjust exit to rotorposition;
    if(c<0)c+=26;
    return (c);             
}

//
// Check if this rotor has passed the notch.
// This function is needed to trigger the next rotor on the left to advance.
// Example: when the rotor steps from from Q to R, this function is true when ringpos is R
//
bool rotor::over_notch() { 
    
    bool has_notched=false;
    
    //check if ring is over the notch
    has_notched=(ringpos==notchpos);
        
    //check for ringtype VI,VII,VIII the second notch from M->N
    if ((rotortype>4)&&(has_notched==false)&&(ringpos==13))
        has_notched=true;
    
    return has_notched;
}

//
// Check if this rotor has on the notch.
// This function is needed to detect the double step scenario.
// Example: when the notch is triggered from Q to R, this function is true when ringpos is Q
//
bool rotor::on_notch() {
    bool on_notch=false;
    
    //check if ring is on the notch
    on_notch=((ringpos+1)%26==notchpos);
        
    //check for ringtype VI,VII,VIII on the second notch from M->N
    if ((rotortype>4)&&(on_notch==false)&&((ringpos+1)%26==13))
        on_notch=true;
    
    return on_notch;
}
