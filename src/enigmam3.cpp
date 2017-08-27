#include "enigmam3.hpp"
#include "rotor.hpp"
#include "plugboard.hpp"
#include "reflector.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

enigmam3::enigmam3()
{
    R1.init(0,0);
    R2.init(1,0);
    R3.init(2,0);
    R1.setpos(0);
    R2.setpos(0);
    R3.setpos(0);

    RF.init(1);
    PB.resetwires();
}

void enigmam3::advance(){

    R3.step();                            // Rotate fast always
    if (R3.over_notch())
          R2.step();                      // Rotate middle when fast is notched
    else 
       if (R2.on_notch()){                // Check double_step scenario
            R2.step();                    // when true rotate middle and slow rotor
            R1.step();
        }

}

void enigmam3::setReflector(char rf){
    
    char rfc=toupper(rf);
    RF.init((int)(rfc-65));
}

void enigmam3::setRotor(int n,int rtype,char ringpos){
    
    ringpos = toupper(ringpos);
    switch(n){
        case 1: R1.init(rtype,(int)(ringpos-65));break;
        case 2: R2.init(rtype,(int)(ringpos-65));break;
        case 3: R3.init(rtype,(int)(ringpos-65));break;
           
    }
}

void enigmam3::setPlug(char a, char b){
    
    
    a=toupper(a);
    b=toupper(b);
    PB.swap((int)(a-65),(int)(b-65));
    
}

void enigmam3::clearPlugs(){
    PB.resetwires();
}


void enigmam3::setRotorpos(int n,char rotorpos){
    
    rotorpos = toupper(rotorpos);
    switch(n){
        case 1: R1.setpos((int)(rotorpos-65));break;
        case 2: R2.setpos((int)(rotorpos-65));break;
        case 3: R3.setpos((int)(rotorpos-65));break;
            
    }
}

char enigmam3::encode(char c){

    int P=(int)c -65;       //convert char to int, enigma classes uses integers

    P=PB.pass(P);
    P=R3.encode(P); 
    P=R2.encode(P); 
    P=R1.encode(P); 
    P=RF.reflect(P); 
    P=R1.reverse(P); 
    P=R2.reverse(P); 
    P=R3.reverse(P);
    P=PB.pass(P);
    
    return (char)(P+65);
}




void enigmam3::display_enigma(){
    
    
    string rotortype[8]={"I","II","III","IV","V","VI","VII","VIII"};
    string reflectortype[3]={"A","B","C"};
    
    cout<<endl;
    for(int i=0;i<26;i++)cout<<"---"; cout<< endl;
    cout<< std::setw(49)<<"E N I G M A (M3)"<<endl<<endl;
    cout<< std::setw(41)<<"UKW : ";
    cout<< reflectortype[RF.gettype()]<<endl;
    cout<< std::setw(41)<<"Walzen : ";
    cout<< rotortype[R1.getrotortype()]<<" ";
    cout<< rotortype[R2.getrotortype()]<<" ";
    cout<< rotortype[R3.getrotortype()];
    cout<< endl;
    cout<< std::setw(41)<<"Ringstellung : ";
    cout<< (char)(R1.getringsetting()+65)<<" ";
    cout<< (char)(R2.getringsetting()+65)<<" ";
    cout<< (char)(R3.getringsetting()+65);
    cout<< endl;
    cout<< std::setw(41)<<"Rotorposition : ";
    cout<<(char)(R1.getringpos()+65)<<" ";
    cout<<(char)(R2.getringpos()+65)<<" ";
    cout<<(char)(R3.getringpos()+65);
    cout<< endl;
    cout<< std::setw(41)<<"Steckerbrett : "<<PB.boardinfo();
    cout<<endl;
    for(int i=1;i<=26;i++)cout<<"---";
    cout<<endl;
   
    
 
}
/*




char encode_char(char c, rotor& R1, rotor& R2, rotor& R3, reflector RF, plugboard& PB){

    int P=(int)c -65;       //convert char to int, enigma classes uses integers

    P=PB.pass(P);
    P=R3.encode(P); 
    P=R2.encode(P); 
    P=R1.encode(P); 
    P=RF.reflect(P); 
    P=R1.reverse(P); 
    P=R2.reverse(P); 
    P=R3.reverse(P);
    P=PB.pass(P);
    
    return (char)(P+65);
}

void scramble_message(rotor& R1, rotor& R2, rotor& R3, reflector RF,plugboard& PB){
    
    string m;
    char c;
    cout<<endl<<"Enter  message: ";
    cin.ignore();
    getline(std::cin,m);
    cout<<endl<<"Enigma message: ";
    
    for (int i=0;i<m.length();i++)
        if(isalpha(m.at(i))){
            c=toupper(m.at(i));
            rotate(R1,R2,R3); 
            cout<<encode_char(c,R1,R2,R3,RF,PB);
        }
        else cout<<" ";
        cout<<endl;
}

*/





