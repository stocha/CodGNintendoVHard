/* 
 * File:   Normaliser.cpp
 * Author: denis
 * 
 * 
 * (p&~q)V(~p&q)
 * (pVq)&(~pV~q)
 *~Xor --> (pV~q)&(~pVq)
 *~Xor --> (p&q)V(~p&~q)
 * 
 * Xor (a&b,c&d)
 * 
 * Created on 4 juillet 2015, 18:20
 */

#include <cstdlib>
#include <iomanip>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <sstream> //this is where istringstream is defined
#include <string>
#include <memory>

using namespace std;
namespace normalizerCNF{
    class Var{
        Var(int value) : value(value){
        }
        
        const int value;
    };
    
}
        
     

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "hello forme normale";
    return 0;
}

