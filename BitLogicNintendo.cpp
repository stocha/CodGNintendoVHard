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

#include "BlN_ext001.h"

/*std::string& inString
 * "00000083 000000e5"
 */



 std::string toStringBs(bitset<512> dat,int size){          
      std::string mystring =
    dat.to_string<char,std::string::traits_type,std::string::allocator_type>();
      
      return mystring.substr(512-size,512);
 }
 


int main(int argc, char** argv) {   
    bitset<512> my (std::string("1001"));
    int size=4;
    cout<< toStringBs(my,size) << endl;
     cout<< toStringBs(applyDirectFun(my,size),size)<<endl;
    return 0;
}

