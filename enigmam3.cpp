#include <iostream>
#include <iomanip>
#include "rotor.h"
#include "reflector.h"

using namespace std;



 void display_rotor(rotor r){

    cout<<", Rotor " << std::setw(3)<<r.getrotortype();
    cout<<", window "<<r.getringpos();
    cout<<", position "<< r.getrotorpos();
    cout<< endl;
 
 }

void rotate(rotor R1, rotor R2, rotor R3){

    R3.step();                            // Rotate fast always
    if (R3.has_notched())
          R2.step();                      // Rotate middle when fast is notched
    else 
       if (R2.is_notched()){                // Check double_step scenario
            R2.step();                    // when true rotate middle and slow rotor
            R1.step();
        }

}



int main()
{
    rotor R1(2,10,0);
    rotor R2(1,3,0);
    rotor R3(0,14,0);
    reflector R(0);

    display_rotor(R1);
    display_rotor(R2);
    display_rotor(R3);

    rotate(R1,R2,R3);    
    int P=23;
    P=R3.encode(P); cout<< "Decoded P in rotor 3: " <<(char)(P+65) <<endl;
    P=R2.encode(P); cout<< "Decoded P in rotor 2: " <<P <<endl;
    P=R1.encode(P); cout<< "Decoded P in rotor 1: " <<P <<endl;
    
    P=R.reflect(P); cout<< "Reflected P in reflector: " <<P <<endl;
    
    P=R1.reverse(P); cout<< "Reversed P in rotor 1: " <<P <<endl;
    P=R2.reverse(P); cout<< "Reversed P in rotor 2: " <<P <<endl;
    P=R3.reverse(P); cout<< "Deversed P in rotor 3: " <<P <<endl;

    return 0;
}





