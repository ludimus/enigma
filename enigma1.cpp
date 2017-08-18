#include <iostream>
#include <iomanip>
#include "rotor.h"
#include "reflector.h"

using namespace std;



 void display_rotor(rotor r,int i){

    cout<<"Rotor "<<i+1;
    cout<<", type " << std::setw(3)<<r.gettype();
    cout<<", ring "<<r.getring();
    cout<<", window "<<r.getwindow();
    cout<<", position "<< r.getpos();
    cout<<", wires "<<r.getwires();
    cout<< endl;
 
 }





int main()
{
    rotor W[3];
    reflector R;
    W[0].settype(4);
    W[0].setpos(7);
    W[0].setring(1);

    W[1].settype(1);
    W[1].setpos(2);
    W[1].setring(1);

    W[2].settype(3);
    W[2].setpos(5);
    W[2].setring(1);

    for (int i=0;i<3;i++)
        display_rotor(W[i],i);
    
    
    char P='X';
    P=W[2].encode(P); cout<< "Decoded P in rotor 3: " <<P <<endl;
    P=W[1].encode(P); cout<< "Decoded P in rotor 2: " <<P <<endl;
    P=W[0].encode(P); cout<< "Decoded P in rotor 1: " <<P <<endl;
    
    P=R.reflect(P); cout<< "Reflected P in reflector: " <<P <<endl;
    
    P=W[0].reverse(P); cout<< "Reversed P in rotor 1: " <<P <<endl;
    P=W[1].reverse(P); cout<< "Decoded P in rotor 2: " <<P <<endl;
    P=W[2].reverse(P); cout<< "Decoded P in rotor 3: " <<P <<endl;


    for (int i=0;i<0;i++){
        W[2].rotate();                      // Rotate fast always
        if (W[2].is_nudged())
            W[1].rotate();                  // Rotate middle when fast is nudged
        else 
          if (W[1].check_doublestep()){     // Check double_step scenario
            W[1].rotate();                  // when true rotate middle and slow rotor
            W[0].rotate();
        }
        
        for(int j=0;j<3;j++)
            display_rotor(W[j],j);
        cout<<endl;
        
    }
    return 0;
 }





