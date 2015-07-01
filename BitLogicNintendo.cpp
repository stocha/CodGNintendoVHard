/* 
 * File:   BitLogicNintendo.cpp
 * Author: Jahan
 *
 * Created on 1 juillet 2015, 13:22
 */

#include <cstdlib>
#include "Tools.h"
#include <iomanip>
#include <bitset>

using namespace std;

/*std::string& inString
 * "00000083 000000e5"
 */

bitset<64> toBitSet(string data){
    unique_ptr<std::istringstream> in=Tools::stringToStdin(data);
    int size=0;
    *in >> size;    
    if(size != 32) {cout << "Unsuported size"; exit(1);}
    
    unsigned int a[32 / 16];
    bitset<32> ab[32 / 16]; 
    for (int i = 0; i < size / 16; i++) {
      *in >> hex >> a[i];
      ab[i]=bitset<32>(a[i]);
    }
    bitset<64> outp;
    
    for(int i=0;i<outp.size();i++){
        int dec=i/32;
        int ind=i%32;
        outp[i]=ab[dec][ind];
    }
    return outp;
}

void  toCout(bitset<64> data){
    cout << data << endl;
    unsigned int a [data.size() / 32];
    bitset<32> ab[data.size() / 32];
    for(int i=0;i<data.size();i++){
        int dec=i/32;
        int ind=i%32;
        ab[dec][ind]=data[i];
    }
    for(int i = 0; i < data.size() / 32; i++)
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
int main(int argc, char** argv) {
    string form="32\n00000001 00000001";
    official(form);
    bitset<64> inpubs= toBitSet(form);
    toCout(inpubs);
    return 0;
}

