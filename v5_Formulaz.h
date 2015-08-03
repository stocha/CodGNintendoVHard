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
     bitset<512> dat;
     int sz;
public:
    //bitField(){};
    bitField(int startSz) : sz(startSz){
    }
    bitField(string strHex){
        
        istringstream in(strHex);
        int size=0;
        in >> size;    

        unsigned int a[size / 16];
        bitset<32> ab[size / 16]; 
        for (int i = 0; i < size / 16; i++) {
          in >> hex >> a[i];
          ab[i]=bitset<32>(a[i]);
        }

        for(int i=0;i<size*2;i++){
            int dec=i/32;
            int ind=i%32;
            dat[i]=ab[dec][ind];
        }        
        
        
        sz=size*2;
                
    }
    
    
    
    long operator[]( std::size_t pos) const{
        return dat[pos]?1:0;
    }
    
    void set(std::size_t at,long value){
        dat[at]=value;
    }
    
    int size(){
        return sz;
    }

    string str();
    string strHex(){

        std::ostringstream sout;
        
        unsigned int a [sz / 32];
        bitset<32> ab[sz / 32];
        for (int i = 0; i < sz; i++) {
            int dec = i / 32;
            int ind = i % 32;
            ab[dec][ind] = dat[i];
        }
        for (int i = 0; i < (sz / 32); i++)
            sout << setfill('0') << setw(8) << hex << ab[i].to_ulong() << " "; // print result       
        sout << endl;        
        
        string res = sout.str();
        return res;
    }


};

class FormulazTests {
public:
    static void testBitField();

};


#endif	/* FORMULAZ_H */

