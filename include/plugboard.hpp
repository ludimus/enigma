#include <string>

#ifndef plugboard_H
#define plugboard_H

class plugboard 
{
    int wires[26];

public:
    // Constructors
    plugboard();
    
    //Plugboard configuration functions

    void swap(int a,int b);
    void resetwires();
    
    //pluboard operations
    int pass(int c);
    
    //show current settings
    std::string boardinfo();

}; 

#endif
