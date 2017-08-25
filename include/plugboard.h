#ifndef plugboard_H
#define plugboard_H

class plugboard 
{
    int wires[26];

public:
    // Constructors
    plugboard();

    void swap(int a,int b);
    int pass(int c);
    void resetwires();
    std::string boardinfo();

}; 

#endif
