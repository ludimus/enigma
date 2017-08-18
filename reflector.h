#ifndef reflector_H
#define reflector_H

class reflector 
{
    char wires[26];

public:
    // Constructors
    reflector();

    void setwires(int rt);
    char reflect(char c);

}; 

#endif
