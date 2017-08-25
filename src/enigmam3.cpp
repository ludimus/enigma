#include <iostream>
#include <iomanip>
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"


using namespace std;

string formatring(int ring){

    string ret;
    ret.push_back((char)(ring+65));
    ret.push_back('-');
    if(ring<10) ret.push_back('0');
    ret+=std::to_string(ring+1);
    return(ret);
}

void display_enigma_menu(rotor& R1, rotor& R2, rotor& R3, reflector& RF, plugboard& PB){
    
    
    string rotortype[8]={"I","II","III","IV","V","VI","VII","VIII"};
    string reflectortye[4]={"B","C","B--","C--"};
    
    cout<<endl;
    for(int i=1;i<=26;i++)cout<<"---"; cout<< endl;
    for(int i=1;i<=26;i++)cout<<std::setw(3)<<(char)(i+64); cout<< endl;
    for(int i=1;i<=26;i++)cout<<std::setw(3)<<i; cout<< endl;
    for(int i=0;i<26;i++)cout<<"---"; cout<< endl;
    cout<< std::setw(49)<<"E N I G M A (M3)"<<endl<<endl;
    cout<< std::setw(41)<<"UKW : ";
    cout<< (char)(RF.gettype()+65)<<endl;
    cout<< std::setw(41)<<"Walzen : ";
    cout<< rotortype[R1.getrotortype()]<<" ";
    cout<< rotortype[R2.getrotortype()]<<" ";
    cout<< rotortype[R3.getrotortype()];
    cout<< endl;
    cout<< std::setw(41)<<"Ringstellung : ";
    cout<< formatring(R1.getringsetting())<<" ";
    cout<< formatring(R2.getringsetting())<<" ";
    cout<< formatring(R3.getringsetting());
    cout<< endl;
    cout<< std::setw(41)<<"Rotorposition : ";
    cout<<(char)(R1.getringpos()+65);
    cout<<(char)(R2.getringpos()+65);
    cout<<(char)(R3.getringpos()+65);
    cout<< endl;
    cout<< std::setw(41)<<"Steckerbrett : "<<PB.boardinfo();
    cout<<endl;
    for(int i=1;i<=26;i++)cout<<"---";
   
    cout<<endl<<"Change [U]KW, Rotor[1][2][3], Position[A][B][C], [S]tecker, [M]essage, [Q]uit:";
 
}

void rotate(rotor& R1,rotor& R2, rotor& R3){

    R3.step();                            // Rotate fast always
    if (R3.over_notch())
          R2.step();                      // Rotate middle when fast is notched
    else 
       if (R2.on_notch()){                // Check double_step scenario
            R2.step();                    // when true rotate middle and slow rotor
            R1.step();
        }

}

void swap_rotor(rotor& R){
    
    int rt;
    char rs;
    
    cout<<"Roter type(1-8):";
    cin>>rt;
    cout<<"Roter Ringsetting(A-Z):";
    cin>>rs;
    rs=toupper(rs);
    R.init(rt-1,(int)(rs-65));
    
}

void swap_plugs(plugboard& PB){
    
    char a,b;
    
    cout<<"First char (A-Z):";
    cin>>a;
    a=toupper(a);
    cout<<"Second char (A-Z):";
    cin>>b;
    b=toupper(b);
    PB.swap((int)(a-65),(int)(b-65));
    
}

void set_rotor(rotor& R){
    
    char rp;

    cout<<"RotorPosition(A-Z):";
    cin>>rp;
    rp=toupper(rp);
    R.setpos((int)(rp-65));
    
}

void swap_ukw(reflector& RF){
    
    char rp;

    cout<<"UKW(A-C):";
    cin>>rp;
    rp=toupper(rp);
    RF.init((int)(rp-65));
    
}

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

int main()
{
    rotor R1(0,0);
    rotor R2(1,0);
    rotor R3(2,0);
    R1.setpos(0);
    R2.setpos(0);
    R3.setpos(0);

    reflector RF(1);
    plugboard PB;
    
    char c;
    while(c!='Q'){
        display_enigma_menu(R1,R2,R3,RF,PB);
        cin>>c;
        c=toupper(c);
        switch(c)
        {
            case '1': swap_rotor(R1);break;
            case '2': swap_rotor(R2);break;
            case '3': swap_rotor(R3);break;
                
            case 'A': set_rotor(R1);break;
            case 'B': set_rotor(R2);break;
            case 'C': set_rotor(R3);break;
                
            case 'S': swap_plugs(PB);break;  
            case 'U': swap_ukw(RF);break;
            
            case 'M': scramble_message(R1,R2,R3,RF,PB);    
            default:;    
                
        }
    }

return 0;
}





