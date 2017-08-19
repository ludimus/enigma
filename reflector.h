#ifndef reflector_H
#define reflector_H

class reflector 
{
    int wires[26];

public:
    // Constructors
    reflector(int n);

    void setwires(int rt);
    int reflect(int c);

}; 

#endif
