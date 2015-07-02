/* 
 * File:   BitLogicNintendo2.h
 * Author: Jahan
 *
 * Created on 2 juillet 2015, 12:02
 */

#ifndef BITLOGICNINTENDO2_H
#define	BITLOGICNINTENDO2_H

#include <cstdlib>
#include <iomanip>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream> 
#include <sstream> //this is where istringstream is defined
#include <string>
#include <memory>


using namespace std;

const int SZVEC = 64;

class Tools {
public:
    Tools();
    Tools(const Tools& orig);
    virtual ~Tools();
    
    static std::unique_ptr<std::istringstream> stringToStdin(string inString );
private:

};

Tools::Tools() {
}

Tools::Tools(const Tools& orig) {
}

Tools::~Tools() {
}

std::unique_ptr<std::istringstream> Tools::stringToStdin(string inString){
    //string inString="00000083 000000e5";
    unique_ptr<std::istringstream> res(new istringstream(inString));
    //std::istringstream sin(inString);
    return res;
}

int myPow(int x, int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;

  int tmp = myPow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}


bitset<SZVEC> applyDirectFun (bitset<SZVEC> dat, int size){
    bitset<SZVEC> out;
    for(int i=0;i<size/2;i++){
        for(int j=0;j<size/2;j++){
            out[i+j]=out[i+j]^(dat[i]&dat[j+size/2]);
        }
    }
    return out;
}

tuple<bitset<SZVEC>, int> toBitSet(string data){
    unique_ptr<std::istringstream> in=Tools::stringToStdin(data);
    int size=0;
    *in >> size;    
    
    unsigned int a[size / 16];
    bitset<32> ab[size / 16]; 
    for (int i = 0; i < size / 16; i++) {
      *in >> hex >> a[i];
      ab[i]=bitset<32>(a[i]);
    }
    bitset<SZVEC> outp;
    
    for(int i=0;i<size*2;i++){
        int dec=i/32;
        int ind=i%32;
        outp[i]=ab[dec][ind];
    }
    return make_tuple(outp,size*2);
}

tuple<bitset<SZVEC>, int> readBitSetFromStdin(){
    int size=0;
    cin >> size;    
    
    unsigned int a[size / 16];
    bitset<32> ab[size / 16]; 
    for (int i = 0; i < size / 16; i++) {
      cin >> hex >> a[i];
      ab[i]=bitset<32>(a[i]);
    }
    bitset<SZVEC> outp;
    
    for(int i=0;i<size*2;i++){
        int dec=i/32;
        int ind=i%32;
        outp[i]=ab[dec][ind];
    }
    return make_tuple(outp,size*2);
}

void  toCout(bitset<SZVEC> data,int size){
    //cout << data << endl;
    unsigned int a [size / 32];
    bitset<32> ab[size / 32];
    for(int i=0;i<size*2;i++){
        int dec=i/32;
        int ind=i%32;
        ab[dec][ind]=data[i];
    }
    for(int i = 0; i < size / 32; i++)
      cout << setfill('0') << setw(8) << hex << ab[i].to_ulong() << " ";       // print result       
    cout<<endl;
}

void official(string data){
    unique_ptr<std::istringstream> in=Tools::stringToStdin(data);
    
    int size;
    *in >> size;

    unsigned int* a = new unsigned int[size / 16]; // <- input tab to encrypt
    unsigned int* b = new unsigned int[size / 16]; // <- output tab

    for (int i = 0; i < size / 16; i++) {   // Read size / 16 integers to a
      *in >> hex >> a[i];
    }

    for (int i = 0; i < size / 16; i++) {   // Write size / 16 zeros to b
      b[i] = 0;
    }	

    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        b[(i + j) / 32] ^= ( (a[i / 32] >> (i % 32)) &
                         (a[j / 32 + size / 32] >> (j % 32)) & 1 ) << ((i + j) % 32);   // Magic centaurian operation

    for(int i = 0; i < size / 16; i++)
      cout << setfill('0') << setw(8) << hex << b[i] << " ";       // print result    
    
    cout<<endl;
    
}

 void testInputOutputCompareRef(){
     //string form="32\nb0c152f9 ebf2831f"; //46508fb7 6677e201
    //string form="64\n0cf5c2bf 9aba68ef c18fb79b de70eef7"; //0cf5c2bf 9aba68ef c18fb79b de70eef7
    //string form="128\nc58f4047 d73fe36a 24be2846 e2ebe432 a30d28bd bda19675 3f95d074 b6f69434"; //0cf5c2bf 9aba68ef c18fb79b de70eef7

     string form1="32\n0000b0c5 0000cd55"; //738377c1 00000000
     string form2="32\nebf2831f b0c152f9";//46508fb7 6677e201
     
     
    bitset<SZVEC> inpubs;int size;
    tie(inpubs,size)= toBitSet(form1);
    toCout(applyDirectFun(inpubs,size),size);
    tie(inpubs,size)= toBitSet(form2);
    toCout(applyDirectFun(inpubs,size),size);    

 }
 
 
std::string toStringBs(bitset<SZVEC> dat, int size) {
    std::string mystring =
            dat.to_string<char, std::string::traits_type, std::string::allocator_type>();

    //cout << "doublageProvisoire pour test" << endl;
    return mystring.substr(SZVEC - size, SZVEC);
} 

#endif	/* BITLOGICNINTENDO2_H */

