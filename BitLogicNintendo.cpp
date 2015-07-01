/* 
 * File:   BitLogicNintendo.cpp
 * Author: Jahan
 *
 * Created on 1 juillet 2015, 13:22
 */

#include <cstdlib>
#include "Tools.h"

using namespace std;

/*std::string& inString
 * "00000083 000000e5"
 */

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
      cout << hex << b[i] << " ";       // print result    
    
}
int main(int argc, char** argv) {
    official("32\n00000083 000000e5");
    return 0;
}

