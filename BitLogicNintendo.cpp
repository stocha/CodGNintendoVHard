/* 
 * File:   BitLogicNintendo.cpp
 * Author: Jahan
 *
 * Created on 1 juillet 2015, 13:22
 */

#include <cstdlib>
#include <iomanip>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "Tools.h"

using namespace std;

const int SZVEC = 64;

#include "BlN_ext001.h"



/*std::string& inString
 * "00000083 000000e5"
 */




std::unordered_set<bitset < SZVEC >> solveIt(bitset<SZVEC> input, bitset<SZVEC> hypoth, int size, int depth) {
    std::unordered_set<bitset < SZVEC >> res;
    int magic[] = {0, size / 2 - 1, size / 2, size - 1};
    
    bool activCond=false;
    bool activate_formul_debug=false;
    unsigned long valHypActDebug=41;
    
    if(activCond)if(depth==0) activate_formul_debug=true;

    if(activate_formul_debug)
      cout << "hyp " << toStringBs(hypoth, size) << " deep= " << depth<<" ";
    //  cout <<"magic ";for(int i=0;i<4;i++)cout << magic[i] ;cout << endl;
    //if( input!=40 || depth==0 )cout <<"input " <<toStringBs(input, size) << "--- depth " << depth << endl;


    for (unsigned int i = 0; i < 16; i++) {
        bitset<SZVEC> v;
        v[magic[0] + depth] = i & 1;
        v[magic[1] - depth] = ((i >> 1) & 1);
        v[magic[2] + depth] = ((i >> 2) & 1);
        v[magic[3] - depth] = ((i >> 3) & 1);

        //  cout<< "v(b hyp) : " << toStringBs(v, size) << endl;

        for (int i = 0; i < depth; i++) {
            v[magic[0] + i] = hypoth[magic[0] + i];
            v[magic[1] - i] = hypoth[magic[1] - i];
            v[magic[2] + i] = hypoth[magic[2] + i];
            v[magic[3] - i] = hypoth[magic[3] - i];
        }

       if(activCond) if(depth>=1 && v==valHypActDebug) activate_formul_debug=true;
            if(activate_formul_debug)
          cout<< "--- depth " << depth << " v(aft hyp) : " << toStringBs(v, size) << endl;        

        // check formula .... left
        bool ext = input[0 + depth];
        bool possible = false;
         if(activate_formul_debug)    cout<<"{";
        for (int i = 0; i < depth + 1; i++) {
            int h = size / 2;
            int riand = i;
            int rilef = h + (depth - i);
            possible = possible^(v[riand] & v[rilef]);
              if(activate_formul_debug)       cout<<"("<<(riand)<<"&"<<(rilef)<<")"<< v[riand] << "&" <<  v[rilef];
        }
        if(activate_formul_debug)     cout<<"}"<<endl;
         // cout << "ext " << ext << " calc "<< possible << endl;
        bool rightFormulaIsPassed = false;
        
         if (depth >= (size / 2) - 1) {
             rightFormulaIsPassed=(ext == possible);
         }else        
        if (ext == possible) {
            // check formula .... right
             if(activate_formul_debug)        cout << " check right formula part inputIs(" << toStringBs(input, size)  << ") " << endl;
            int rightEdge = size - 1;
            ext = input[size - 2 - depth]; // cout << "Extern bit " << " (" <<(size-2-depth) <<") is " << input[size-2-depth] <<endl;
            possible = false;
              if(activate_formul_debug)       cout<<"right {";
            for (int i = 0; i < depth + 1; i++) {
                int h = size / 2;
                int riand = h - i - 1;
                int rilef = rightEdge - depth + i;
                possible = possible^(v[riand] & v[rilef]);
             if(activate_formul_debug)         cout<<"("<<(riand)<<"&"<<(rilef)<<")"<< v[riand] << "&" <<  v[rilef];
            }
             if(activate_formul_debug)     cout<<"}"<<endl; 

              // cout << "right form " <<" ext "<< ext << " possible "  << possible << endl;

            rightFormulaIsPassed = (ext == possible);
            //  cout << "righ formula is passed " << rightFormulaIsPassed << endl;
        }


        if (rightFormulaIsPassed) {

            if (depth >= (size / 2) - 1) {
                //   cout << " adding validated " <<  toStringBs(v, size) << endl;

                res.insert(v);

            } else {
                std::unordered_set<bitset < SZVEC >> sub = solveIt(input, v, size, depth + 1);
              if(activate_formul_debug)            cout << "++++++++ back to "<< depth << " " << "hyp " << toStringBs(hypoth, size) << " deep= " << depth<<" " <<endl;
                for (const auto& subv : sub) {
                    res.insert(subv);
                    /* ... process elem ... */
                }
            }
        }
    } // fin parcours hypotheses

    return res;
}

    struct {
        bool operator()(bitset < SZVEC > a, bitset < SZVEC > b)
        {   
            for(int i=a.size()-1;i>=0;i--){
                if(a[i]==true && b[i]==false) return false;
                if(a[i]==false && b[i]==true) return true;
            }
            return false;
        }   
    } customLess;
std::vector<bitset < SZVEC >> sortedFunctionInversion(bitset<SZVEC> input, int size) {
    std::unordered_set<bitset < SZVEC >> unres=solveIt(input,input,size,0);
    std::vector<bitset < SZVEC >> res;
                for (const auto& subv : unres) {
                    res.push_back(subv);
                } 
        std::sort (res.begin(), res.end(),customLess);
    return res;

}

std::string formula(int size) {
    std::string res;
    std::string tmp[size];
    res += "Formula ";
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            std::stringstream sstm;
            int k = j + size / 2;
            sstm << "(" << i << "&" << k << ")";
            tmp[i + j] += "" + sstm.str();
            ;
        }

    }
    for (int i = 0; i < size; i++) {
        res += tmp[i];
        res += "|";
    }


    return res;
}

void testMyFunctionWithDifferentManualSize() {
    testInputOutputCompareRef();
    bitset<SZVEC> my;
    int sz = 10;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    for (int i = 0; i < myPow(2, sz); i++) {
        my = i;

        cout << toStringBs(my, sz) << " -> ";
        cout << toStringBs(applyDirectFun(my, sz), sz) << endl;
    }
    cout << "----------- END OF DIRECT --------" << endl;

    for (int i = 0; i < myPow(2, sz-1); i++) {
        //for (int i = 0; i < 0; i++) {
        my = i;
        cout << " inverting " << toStringBs(my, sz) << endl;
        std::vector<bitset < SZVEC >> res = sortedFunctionInversion(my, sz);

        {
            int elemind = 0;
            for (const auto& elem : res) {
                cout << (elemind++) << " : " << toStringBs(elem, sz) << endl;
            }
        }

    }
}

void testMyFunctionWithOneManualSize() {
    testInputOutputCompareRef();
    bitset<SZVEC> my;
    int sz = 8;
    unsigned int val = 41;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    for (int i = val; i < val + 1; i++) {
        my = i;

        cout << toStringBs(my, sz) << " -> ";
        cout << toStringBs(applyDirectFun(my, sz), sz) << endl;
        my=applyDirectFun(my, sz);
 
    }
    cout << "----------- END OF DIRECT --------" << endl;

    for (int i = val; i < val + 1; i++) {
        //for (int i = 0; i < 0; i++) {

        cout << " inverting " << toStringBs(my, sz) << endl;
        std::unordered_set<bitset < SZVEC >> res = solveIt(my, my, sz, 0);

        {
            int elemind = 0;
            for (const auto& elem : res) {
                cout << (elemind++) << " : " << toStringBs(elem, sz) << endl;
            }
        }

    }
}

void testMyInvertingWithManualSize(){
    std::unordered_set<bitset < SZVEC >> done;
    
    bitset<SZVEC> my;
    int sz = 8;
    unsigned int val = 0x0e24;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    for (int i = 0; i < myPow(2, sz); i++) {
        my = i;

        cout << toStringBs(my, sz) << " -> ";
        cout << toStringBs(applyDirectFun(my, sz), sz) << endl;
        bitset<SZVEC> myori=my;
        my=applyDirectFun(my, sz);
        
        if(done.find(my)==done.end()){
            done.insert(my);

                cout << " inverting " << toStringBs(myori, sz) << endl;
                std::unordered_set<bitset < SZVEC >> res = solveIt(my, my, sz, 0);
                {
                    int elemind = 0;
                    for (const auto& elem : res) {
                        cout << (elemind++) << " : " << toStringBs(elem, sz) << endl;
                    }
                }   
                if(res.find(myori)==res.end()){
                    cout << " ERROR " << toStringBs(myori,sz) << " not found " << endl;
                }
        }
 
    }
    cout << "----------- END OF DIRECT --------" << endl;

  
}

void showSomeDisplayVariableSize() {
    testInputOutputCompareRef();
    bitset<SZVEC> my;
    int size = 6;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;      
    //cout << formula(size*2) << endl;
    for (int sz = 0; sz <= size; sz++) {
        cout << formula(sz) << endl;
        for (int i = 0; i < myPow(2, sz); i++) {
            my = i;

            cout << toStringBs(my, sz) << " -> ";
            cout << toStringBs(applyDirectFun(my, sz), sz) << endl;
        }
    }
}

void applyRealCase(){
    string data="32\n000073af 00000000";
    int size;
    bitset<SZVEC> bs;
    tie(bs,size)=toBitSet(data);
    std::vector<bitset < SZVEC >> res= sortedFunctionInversion(bs,size);
    for(int i=0;i<res.size();i++){
        toCout(res[i],size);
    }
    
    
}

void applyStdIn(){
    int size;
    bitset<SZVEC> bs;
    tie(bs,size)=readBitSetFromStdin();
    std::vector<bitset < SZVEC >> res= sortedFunctionInversion(bs,size);
    for(int i=0;i<res.size();i++){
        toCout(res[i],size);
    }
    
    
}

int main(int argc, char** argv) {
    
    //applyRealCase();
    //applyStdIn();
    
   // testMyInvertingWithManualSize();
    
    cout << formula(8) << endl;
    //cout << formula(4) << endl;
    testMyFunctionWithOneManualSize();
    //testMyFunctionWithDifferentManualSize();

    //testMyFunctionWithDifferentManualSize();
    //testMyFunctionWithOneManualSize

    //bitset<SZVEC> my;
    //int size = 16;

    //for (int sz = 16; sz <= size; sz++) {
    //    cout << formula(sz) << endl;
    //}

    return 0;
}

