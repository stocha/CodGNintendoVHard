/* 
 * File:   Formulaz.h
 * Author: denis
 *
 * Created on 9 juillet 2015, 19:01
 */

#ifndef FORMULAZ_H
#define	FORMULAZ_H

#include <cstdlib>
#include <iomanip>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream> //this is where istringstream is defined
#include <string>
#include <memory>
using namespace std;

class SoluSimp{
    
    int sz;
    
public :    
    SoluSimp(int sz){
        this->sz=sz;
    }
public :
    int nbXor(int at){
        //if(at>=sz/2) return 0;
        int d=(sz-1)/2 - at;
        if(d>=0) return ((sz/2-1) -d +1);
        cout << "ERROR " << at << " out of formbounds" ;
        exit(1);
        return 0;
    }
    int coefL(int at,int num){
        return (at-num);
    }
    int coefLsec(int at,int num){
        return sz-1-at-num;
    }
    int coefR(int at,int num){
        return (at-coefL(at,num));
    }
    int coefRsec(int at,int num){
        return (at-coefLsec(at,num));
    }    

    
    void debug_coef(){
        for(int i=0;i<sz/2;i++){
            cout << i << " :: ";
            for(int j=0;j<nbXor(i);j++){
                cout << "(" << coefL(i,j) << "&" << coefR(i,j) << ")+";
            }
            cout<<" & "<<endl;
        }
        for(int i=0;i<sz/2 -1;i++){
            cout << i << " :: ";
            for(int j=0;j<nbXor(i);j++){
                cout << "(" << coefLsec(i,j) << "&" << coefRsec(i,j) << ")+";
            }
            cout<<" & "<<endl;
        }        
    
    }
 };



class Formulaz {
public:
    Formulaz();
    Formulaz(const Formulaz& orig);
    virtual ~Formulaz();

    virtual bool evaluate(const vector<bool>& it) = 0;
    virtual int inputSize() = 0;
private:

};

class bitField {
private:
    vector<bool> dat;

public :
    bitField();
    bitField(int startSz);
    bitField(string strHex);
    
    vector<bool> v(){
        return dat;
    }
    
    string str();
    string strHex();
    
    
};


#endif	/* FORMULAZ_H */

