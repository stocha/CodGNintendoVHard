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
 
 std::string formula(int size){
     std::string res;
     std::string tmp[size];
     res+="Formula ";
     for(int i=0;i<size/2;i++){
         for(int j=0;j<size/2;j++){
             std::stringstream sstm;
             int k=j+size/2;
            sstm << "(" << i << "&" << k<<")";
             tmp[i+j]+=""+sstm.str();;
         }
         
     }
     for(int i=0;i<size;i++){
         res+=tmp[i];
         res+="|";
     }
     
     
     return res;
 }

int main(int argc, char** argv) {   
    testInputOutputCompareRef();
    
    bitset<512> my;
        int size=8;
      
    cout << formula(size/2) << endl;         
    cout << formula(size) << endl;     
    cout << formula(size*2) << endl;
    for(int i=0;i<0xFF;i++){
        my=i;
        
        cout<< toStringBs(my,size) << " -> ";
        cout<< toStringBs(applyDirectFun(my,size),size)<<endl;        
    }
    

    
    

    return 0;
}

