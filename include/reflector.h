#ifndef reflector_H
#define reflector_H

class reflector 
{
    int wires[26];
    int reflectortype;

public:
    // Constructors
    reflector();
    reflector(int n);
    
    // Getters
    int gettype();
    
    // functions
    void init(int rt);
    void setwires(int rt);
    int reflect(int c);

}; 

#endif
