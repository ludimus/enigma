#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "enigmam3.hpp"

using namespace std;


void set_rotors(enigmam3& E, char* rp){
    
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
        if(i==0) E.setRotor(1,(int)(rtype-49),rpos);
        if(i==2) E.setRotor(2,(int)(rtype-49),rpos);
        if(i==4) E.setRotor(3,(int)(rtype-49),rpos);
                
    }
    
}

void set_plugs(enigmam3& E, char* plugs){
    
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
        E.setPlug(a,b);
        if(d!=':') i=30;  
    }
    
}

void set_key(enigmam3& E, char* rp){
    
    string keyfailed ="-k Incorrect messageKey example: HFA ";
    
    char rtype,rpos;
    
    for (int i=0;i<3;i++){
        rpos=toupper(rp[i]);    
        if ((rpos<'A')|| (rpos>'Z')){
            cout<<keyfailed<<endl;
            exit(1);                
        }
        if(i==0) E.setRotorpos(1,rpos);
        if(i==1) E.setRotorpos(2,rpos);
        if(i==2) E.setRotorpos(3,rpos);
                
    }
    
}

void show_usage(){
    cout<<endl<<"Switches:"<<endl;
    cout<<"-u Umkehrwalze(reflector)  : -u A"<<endl;
    cout<<"-w Walze (Rotors and ring) : -w 1A2D4H"<<endl;
    cout<<"-k MessageKey              : -u ANK"<<endl;
    cout<<"-p Plugboard               : -p AB or -p AB:CD:EF"<<endl;
    cout<<"-h This message"<<endl;
    cout<<endl<<"use stdin and stdout for messages to encrypt"<<endl<<endl;
    cout<< "Example: Reflector B, Rotors II I IV, ringssetting AAB, messagekey RTF, plugs AB CD HR MP ZX WO"<<endl;
    cout<< "         encryptM3 -u B -w 2a1a4b -k rtf -p  ab:cd:hr:mp:zx:wo < in.txt > out.M3"<<endl<<endl;    
    exit(0);
}

int main(int argc, char* argv[])
{
    
    enigmam3 E;
    
    // process command line arguments
    int c;
    while( ( c = getopt(argc, argv, "u:w:k:p:h") ) != -1 )
        {
            switch(c)
            {
                case 'u': E.setReflector(optarg[0]);break;
                case 'w': set_rotors(E,optarg);break;
                case 'k': set_key(E,optarg);break;
                case 'p': set_plugs(E,optarg);break;   
                case 'h': show_usage();break;
            }
        }
    //process stdin
    //E.display_enigma();
    string m;
    char p;
    int numalpha=0;
    while(getline(cin, m)) {
        for (int i=0;i<m.length();i++)
            if(isalpha(m.at(i))) {
                p=toupper(m.at(i));
                E.advance(); 
                cout<<E.encode(p);
                numalpha++;
                //format output 5 columns of 4 char;
                if((numalpha%4==0)&&(numalpha%20!=20))cout<<" ";
                if(numalpha%20==0)cout<<endl;
            }
            
    }
    cout<<endl;
    
return 0;
}





