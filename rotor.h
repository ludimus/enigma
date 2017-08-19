#ifndef rotor_H
#define rotor_H

class rotor 
{
    int rotortype;
    int rotorpos;
    int ringpos;
    int notchpos;
    char wires[26];
    char wiresback[26];

public:
    // Constructors
    rotor();
    rotor(int type,int rotor, int ring);
    
    //Getters
    std::string  getrotortype();
    int getrotorpos();
    int getringpos();

    //Enigma operations on rotor
    void step();
    int encode(int c);
    int reverse(int c);
    bool has_notched();
    bool is_notched();

}; 

#endif
