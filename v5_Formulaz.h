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

