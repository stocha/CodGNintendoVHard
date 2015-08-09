/* 
 * File:   Formulaz.cpp
 * Author: denis
 * 
 * Created on 9 juillet 2015, 19:01
 */
#include "v5_Formulaz.h"

Formulaz::Formulaz() {
}

Formulaz::Formulaz(const Formulaz& orig) {
}

Formulaz::~Formulaz() {
}

void FormulazTests::testBitField(){

    cout << "Test BitField" << endl;
    
    string form="16\nb0c1 52f9";
    bitField bf(form);
    
    cout << bf.strHex() << endl;
    cout << bf.str() << endl;
    
    
    bitField rf(4);
    
    int nbVal=20;
    for(int i=0;i<nbVal;i++){
        rf.randomize();
        cout << rf.str() << endl;
    }
    nbVal=16;
    cout << "----------- INCR ------------" << endl;
    for(int i=0;i<nbVal;i++){
        ++rf;
        cout << rf.str() << endl;
    }
    
}

