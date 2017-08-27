#include <iostream>
#include <iomanip>
#include "enigmam3.hpp"


using namespace std;


void display_enigma_menu(enigmam3& E){
    
    
    cout<<endl;
    for(int i=1;i<=26;i++)cout<<"---"; cout<< endl;
    for(int i=1;i<=26;i++)cout<<std::setw(3)<<(char)(i+64); cout<< endl;
    for(int i=1;i<=26;i++)cout<<std::setw(3)<<i;
    E.display_enigma();
   
    cout<<endl<<"Change [U]KW, Rotor[1][2][3], Position[A][B][C], [S]tecker, [M]essage, [Q]uit:";
 
}


void swap_rotor(enigmam3& E,int r){
    
    char rt;
    char rs;
    
    cout<<"Rotor type(1-8):";
    cin>>rt;
    cout<<"Rotor Ringsetting(A-Z):";
    cin>>rs;
    rs=toupper(rs);
    E.setRotor(r,(int)(rt-49),rs);
}

void swap_plugs(enigmam3& E){
    
    char a,b;
    
    cout<<"First char (A-Z):";
    cin>>a;
    a=toupper(a);
    cout<<"Second char (A-Z):";
    cin>>b;
    b=toupper(b);
    E.setPlug(a,b);
    
}

void set_rotor_pos(enigmam3& E, int r){
    
    char rp;

    cout<<"RotorPosition(A-Z):";
    cin>>rp;
    rp=toupper(rp);
    E.setRotorpos(r,rp);
   
    
}

void swap_ukw(enigmam3& E){
    
    char rt;

    cout<<"UKW(A-C):";
    cin>>rt;
    rt=toupper(rt);
    E.setReflector(rt);
    
}


void scramble_message(enigmam3& E){
    
    string m;
    char c;
    cout<<endl<<"Enter  message: ";
    cin.ignore();
    getline(std::cin,m);
    cout<<endl<<"Enigma message: ";
    
    for (int i=0;i<m.length();i++)
        if(isalpha(m.at(i))){
            c=toupper(m.at(i));
            E.advance(); 
            cout<<E.encode(c);        }
        else cout<<" ";
        cout<<endl;
}

int main()
{
    
    enigmam3 E;
    
    char c;
    while(c!='Q'){
        display_enigma_menu(E);
        cin>>c;
        c=toupper(c);
        switch(c)
        {
            case '1': swap_rotor(E,1);break;
            case '2': swap_rotor(E,2);break;
            case '3': swap_rotor(E,3);break;
                
            case 'A': set_rotor_pos(E,1);break;
            case 'B': set_rotor_pos(E,2);break;
            case 'C': set_rotor_pos(E,3);break;
                
            case 'S': swap_plugs(E);break;  
            case 'U': swap_ukw(E);break;
            
            case 'M': scramble_message(E);break;    
            default:;    
                
        }
    }

return 0;
}





