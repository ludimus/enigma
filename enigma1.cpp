#include <iostream>
#include "rotor.h"
using namespace std;

int main()
{
    rotor R[3];

    R[2].settype(4);
    R[2].setpos(2);
    R[1].setpos('Z');

    for (int i=0;i<3;i++){
        cout<<"Rotor "<<i+1<<", type " << R[i].gettype();
        cout<<", position "<<R[i].getpos() << endl;
    }
    return 0;
 }
