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
#include <vector>

using namespace std;

#include "BlN_ext001.h"

/*std::string& inString
 * "00000083 000000e5"
 */

 std::vector<bitset<512>> solveIt(bitset<512> input,bitset<512> hypoth,int size,int depth){
    std::vector<bitset<512>> res(128);
    int magic[]={0,size/2-1,size/2+1,size-1};
    for(int i=0;i<4;i++){
        magic[i]+=depth;        
    }
    for(unsigned int i=0;i<16;i++){
        bitset<512> v;
        v[magic[0]]=i&1;
        v[magic[1]]=(i>>1 & 1);
    }
    
    return res;
}

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
 
 void showSomeDisplayVariableSize(){
    testInputOutputCompareRef();
    
    bitset<512> my;
        int size=6;
      
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;
    
    for(int sz=0;sz<=size;sz++){
        cout << formula(sz) << endl;    
        for(int i=0;i<myPow(2,sz);i++){
            my=i;

            cout<< toStringBs(my,sz) << " -> ";
            cout<< toStringBs(applyDirectFun(my,sz),sz)<<endl;        
        }
    

    }
    
     
 
 }

int main(int argc, char** argv) {   
    bitset<512> my;
        int size=16;
      
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;
    
    for(int sz=16;sz<=size;sz++){
        cout << formula(sz) << endl;       
    }

    return 0;
}

