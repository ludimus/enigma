#include "rotor.hpp"
#include "reflector.hpp"
#include "plugboard.hpp"


#ifndef enigmam3_H
#define enigmam3_H

class enigmam3 
{
    rotor R1;
    rotor R2;
    rotor R3;
    plugboard PB;
    reflector RF;

    
    
public:
    // Constructors
    enigmam3();
    
    //configure enigma functions   
    void setRotor(int r, int type, char ring);
    void setRotorpos(int r, char rpos);
    void setReflector(char rf);
    void setPlug(char a, char b);
    void clearPlugs();
    
    // enigma operations
    void advance();
    char encode (char c);
    
    // display function for all settings
    void display_enigma();
}; 

#endif
