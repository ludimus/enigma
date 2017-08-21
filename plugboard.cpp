#include <iostream>
#include <string>
#include "plugboard.h"
using namespace std;



plugboard::plugboard(){
    resetwires();
}

void plugboard::resetwires(){
    for (int i=0;i<26;i++)
        wires[i]=i;
}

int plugboard::pass(int c){
    return (wires[c]);
}

void plugboard::swap(int a, int b){
    
    //remove old cables first
    for(int i=0;i<26;i++){
        if (wires[i]==a) wires[i]=i;
        if (wires[i]==b) wires[i]=i;
    }
    //place new cable
    wires[a]=b;
    wires[b]=a;
}

std::string plugboard::boardinfo(){
    string s="";
    bool processed[26];
    
   for (int i=0;i<26;i++)
       processed[i]=false;
    
    for (int i=0;i<26;i++)
        if ((!processed[i])&&(wires[i]!=i)){
            s.push_back((char)(i+65));
            s.push_back((char)(wires[i]+65));
            s.push_back(' ');
            processed[wires[i]]=true;
            
        }
    return(s);
}

