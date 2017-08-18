#ifndef rotor_H
#define rotor_H

class rotor 
{
    int rotortype;
    int rotorring;
    int rotorpos;

public:
    rotor();
    rotor(int t,int r, int p);
    
    void settype(int rt);
    void setpos(char rp);
    void setpos(int rp);
    void setring(int rp);
    std::string  gettype();
    char getpos();
    char getring();


    bool rotate();
    char encode(char c);
    char decode(char c);



}; 

#endif
