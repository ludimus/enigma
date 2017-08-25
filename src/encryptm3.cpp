#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"


using namespace std;

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

void set_plugs(plugboard& PB, char* plugs){
    
    string plugfailed ="-p Incorrect Plugsettings example: AB:EF:TH to swap AB EF TH";
    
    char a,b,d;
    
    for (int i=0;i<30;i+=3){
        a=toupper(plugs[i]);    
        b=toupper(plugs[i+1]);
        d=plugs[i+2];
        if ((a<'A')|| (a>'Z')||(b<'A')|| (b>'Z')){
            cout<<plugfailed<<endl;
            exit(1);                
        }
        PB.swap((int)(a-65),(int)(b-65));
        if(d!=':') i=30;  
    }
    
}

void set_key(rotor& R1, rotor& R2, rotor& R3, char* rp){
    
    string keyfailed ="-k Incorrect messageKey example: HFA ";
    
    char rtype,rpos;
    
    for (int i=0;i<3;i++){
        rpos=toupper(rp[i]);    
        if ((rpos<'A')|| (rpos>'Z')){
            cout<<keyfailed<<endl;
            exit(1);                
        }
        if(i==0) R1.setpos((int)(rpos-65));
        if(i==1) R2.setpos((int)(rpos-65));
        if(i==2) R3.setpos((int)(rpos-65));
                
    }
    
}

void set_rotors(rotor& R1, rotor& R2, rotor& R3, char* rp){
    
    string rotorfailed ="-w Incorrect Rotorsetting, example: 1A2B4K for rotors I II IV with ringstellung ABK";
    
    char rtype,rpos;
    
    for (int i=0;i<6;i+=2){
        rtype=rp[i];
        rpos=toupper(rp[i+1]);    
        if(rtype<'1' || rtype>'8'){
            cout<<rotorfailed<<endl;
            exit(1);                
        }
        if ((rpos<'A')|| (rpos>'Z')){
            cout<<rotorfailed<<endl;
            exit(1);                
        }
        if(i==0) R1.init((int)(rtype-49),(int)(rpos-65));
        if(i==2) R2.init((int)(rtype-49),(int)(rpos-65));
        if(i==4) R3.init((int)(rtype-49),(int)(rpos-65));
                
    }
    
}

void set_ukw(reflector& RF,char* rp){
    
    
    char rfc=toupper(rp[0]);
        if((rfc<'A') || (rfc>'C')){
            cout<<"-u Enigma M3 reflector options: [a-c][A-C] "<<endl;
            exit(1);
        }
        RF.init((int)(rfc-65));
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

void show_usage(){
    cout<<endl<<"Switches:"<<endl;
    cout<<"-u Umkehrwalze(reflector)  : -u A"<<endl;
    cout<<"-w Walze (Rotors and ring) : -w 1A2D4H"<<endl;
    cout<<"-k MessageKey              : -u ANK"<<endl;
    cout<<"-p Plugboard               : -p AB or -p AB:CD:EF"<<endl;
    cout<<"-h This message"<<endl;
    cout<<endl<<"use stdin and stdout for messages to encrypt"<<endl<<endl;
    cout<< "Example: Reflector B, Rotors II I IV, ringstelling AAB, messagekey RTF, plugs AB CD HR MP ZX WO"<<endl;
    cout<< "         encryptM3 -u B -w 2a1a4b -k rtf -p  ab:cd:hr:mp:zx:wo < in.txt > out.M3"<<endl<<endl;    
    exit(0);
}

int main(int argc, char* argv[])
{
    // create Enigma M3 with defaults:
    // Rotors I II III, ringstelling AAA, messagekey AAA, reflector B, plugs none
    
    rotor R1(0,0);
    rotor R2(1,0);
    rotor R3(2,0);
    R1.setpos(0);
    R2.setpos(0);
    R3.setpos(0);

    reflector RF(1);
    plugboard PB;
    
    // process command line arguments
    int c;
    while( ( c = getopt(argc, argv, "u:w:k:p:h") ) != -1 )
        {
            switch(c)
            {
                case 'u': set_ukw(RF,optarg);break;
                case 'w': set_rotors(R1,R2,R3,optarg);break;
                case 'k': set_key(R1,R2,R3,optarg);break;
                case 'p': set_plugs(PB,optarg);break;   
                case 'h': show_usage();break;
            }
        }
    //process stdin
    string m;
    char p;
    char numalpha=0;
    while(getline(cin, m)) {
        for (int i=0;i<m.length();i++)
            if(isalpha(m.at(i))) {
                p=toupper(m.at(i));
                rotate(R1,R2,R3); 
                cout<<encode_char(p,R1,R2,R3,RF,PB);
                numalpha++;
                // format output 4 columns of 5 characters:
                if((numalpha%5==0)&&(numalpha%20!=0)) cout<<" ";
                if(numalpha%20==0) cout<<endl;
            }
            
    }
    cout<<endl;
    
return 0;
}





