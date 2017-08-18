#ifndef rotor_H
#define rotor_H

class rotor 
{
    int rotortype;
    int rotorring;
    int rotorpos;
    char wires[26];
    char wiresback[26];
    char nudge;

public:
    // Constructors
    rotor();
    rotor(int t,int r, int p);
    
    //Setters
    void settype(int rt);
    void setpos(char rp);
    void setpos(int rp);
    void setring(int rp);
    void setwires(int rt);
    //Getters
    std::string  gettype();
    std::string  getwires();
    char getpos();
    char getwindow();
    char getring();

    //Enigma operations on rotor
    void rotate();
    char encode(char c);
    char reverse(char c);
    bool is_nudged();
    bool check_doublestep();

}; 

#endif
