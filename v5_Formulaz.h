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

class SoluSimp {
    int sz;

public:

    SoluSimp(int sz) {
        this->sz = sz;
    }
public:

    int nbXor(int at) {
        //if(at>=sz/2) return 0;
        int d = (sz - 1) / 2 - at;
        if (d >= 0) return ((sz / 2 - 1) - d + 1);
        cout << "ERROR " << at << " out of formbounds";
        exit(1);
        return 0;
    }

    int coefL(int at, int num) {
        return (at - num);
    }

    int coefLsec(int at, int num) {
        return sz / 2 - 1 + num - at;
    }

    int coefR(int at, int num) {
        return num + sz / 2;
    }

    int coefRsec(int at, int num) {
        return sz / 2 - 1 - num + sz / 2;
    }

    void debug_coef() {

        const int fillnb = 2;
        for (int i = 0; i < sz / 2; i++) {
            cout << setfill('0') << setw(3) << i << " :: ";
            for (int j = 0; j < nbXor(i); j++) {
                cout << setfill('0') << "(" << setw(fillnb) << coefL(i, j) << "&" << setw(fillnb) << coefR(i, j) << ")+";
            }
            cout << " & " << endl;

            if (i + 1 == sz / 2) break;
            cout << setfill('0') << setw(3) << i << " :: ";
            for (int j = 0; j < nbXor(i); j++) {
                cout << setfill('0') << "(" << setw(fillnb) << coefLsec(i, j) << "&" << setw(fillnb) << coefRsec(i, j) << ")+";
            }
            cout << " & " << endl;
        }
        //        for(int i=0;i<sz/2 -1;i++){
        //            cout << i << " :: ";
        //            for(int j=0;j<nbXor(i);j++){
        //                cout << "(" << coefLsec(i,j) << "&" << coefRsec(i,j) << ")+";
        //            }
        //            cout<<" & "<<endl;
        //        }        

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

public:
    //bitField(){};
    bitField(int startSz) : dat(startSz){
        dat.resize(startSz);
    }
    bitField(string strHex);
    
    
    
    long operator[]( std::size_t pos) const{
        return dat[pos]?1:0;
    }
    
    void set(long v, std::size_t at){
        dat[at]=v;
    }
    
    int size(){
        return dat.size();
    }

    vector<bool> v() {
        return dat;
    }

    string str();
    string strHex();


};

class FormulazTests {
public:
    static void testBitField();

};


#endif	/* FORMULAZ_H */

