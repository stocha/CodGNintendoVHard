/* 
 * File:   Formulaz.cpp
 * Author: denis
 * 
 * Created on 9 juillet 2015, 19:01
 */
#include "v5_Formulaz.h"

bitField applyEncode(bitField in)
{
        int sz=in.size();
        bitField rr(sz);
        for(int i=0;i<(sz/2);i++){
            for(int j=0;j<(sz/2);j++){
                rr.set(i+j,rr[i+j]^(in[i]&in[j+(sz/2)]));
            }            
        }
        
        return rr;
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
        cout << rf.str() << "->" << applyEncode(rf).str() << endl;
    }
    nbVal=16;
    rf.clear();
    cout << "----------- INCR ------------" << endl;
    for(int i=0;i<nbVal;i++){
        ++rf;
        cout << rf.str() << "->" << applyEncode(rf).str() << endl;
    }
    
}


void FormulazTests::testInvertRef(){
cout << "----------- ##### ------------" << endl;
    cout << "Test InvertRef" << endl;
    cout << "----------- --- ------------" << endl;
    bitField bf(4);
    refInvert ri;
    
    int nbVal=0;
    
    nbVal=16;
    bf.clear();
    cout << "----------- INCR ------------" << endl;
    for(int i=0;i<nbVal;i++){
        ++bf;
        cout << bf.str() << "->" <<  "" << endl ;
        for( bitField e : ri.invert(bf)){
           cout << "----->" <<  e.str() << endl ;
        }
        
    }
    
}

void testCompImpl(){
    int nbBit=8;
    
    SoluSimp ss(nbBit);
    ss.debug_coef();
    
    refInvert refInv;
    seqInvert seqInv;
    compareImpl imp(&refInv,&seqInv);   
    //compareImpl imp(&refInv,&refInv);
    imp.compareThem(nbBit,20);
}

void FormulazTests::testAll(){
    testInvertRef();
    testCompImpl();
    //testBitField();

}


