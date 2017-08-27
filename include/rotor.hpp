#ifndef rotor_H
#define rotor_H

class rotor 
{
    int rotortype;
    int rotorpos;
    int ringpos;
    int ringsetting;
    int notchpos;
    char wires[26];
    char wiresback[26];

public:
    // Constructors
    rotor();
    rotor(int type, int ring);
    void init(int type, int ring);
    
    //Getters
    int getrotortype();
    int getrotorpos();
    int getringpos();
    int getringsetting();

    //Enigma operations on rotor
    void step();
    void setpos(int p);
    int encode(int c);
    int reverse(int c);
    bool over_notch();
    bool on_notch();

}; 

#endif
