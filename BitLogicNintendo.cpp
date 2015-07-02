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

#include "BlN_ext001.h"

/*std::string& inString
 * "00000083 000000e5"
 */

std::unordered_set<bitset < 512 >> solveIt(bitset<512> input, bitset<512> hypoth, int size, int depth) {
    std::unordered_set<bitset < 512 >> res;
    int magic[] = {0, size / 2 - 1, size / 2, size - 1};

    //  cout << "hyp " << toStringBs(hypoth, size) << " deep= " << depth<<" ";
    //  cout <<"magic ";for(int i=0;i<4;i++)cout << magic[i] ;cout << endl;


    for (unsigned int i = 0; i < 16; i++) {
        bitset<512> v;
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

      //    cout<< "v(aft hyp) : " << toStringBs(v, size) << endl;        

        // check formula .... left
        bool ext = input[0 + depth];
        bool possible = false;
        // cout<<"{";
        for (int i = 0; i < depth + 1; i++) {
            int h = size / 2;
            int riand = i;
            int rilef = h + (depth - i);
            possible = possible^(v[riand] & v[rilef]);
          //       cout<<"("<<(riand)<<"&"<<(rilef)<<")"<< v[riand] << "&" <<  v[rilef];
        }
         //cout<<"}"<<endl;
         // cout << "ext " << ext << " calc "<< possible << endl;
        bool rightFormulaIsPassed = false;
        
         if (depth >= (size / 2) - 1) {
             rightFormulaIsPassed=(ext == possible);
         }else        
        if (ext == possible) {
            // check formula .... right
            //     cout << " check right formula part inputIs(" << toStringBs(input, size)  << ") " << endl;
            int rightEdge = size - 1 - depth;
            ext = input[size - 2 - depth]; // cout << "Extern bit " << " (" <<(size-2-depth) <<") is " << input[size-2-depth] <<endl;
            possible = false;
               //  cout<<"right {";
            for (int i = 0; i < depth + 1; i++) {
                int h = size / 2;
                int riand = h - i - 1;
                int rilef = rightEdge - i;
                possible = possible^(v[riand] & v[rilef]);
           //       cout<<"("<<(riand)<<"&"<<(rilef)<<")"<< v[riand] << "&" <<  v[rilef];
            }
             // cout<<"}"<<endl; 

              // cout << "right form " <<" ext "<< ext << " possible "  << possible << endl;

            rightFormulaIsPassed = (ext == possible);
            //  cout << "righ formula is passed " << rightFormulaIsPassed << endl;
        }


        if (rightFormulaIsPassed) {

            if (depth >= (size / 2) - 1) {
                //   cout << " adding validated " <<  toStringBs(v, size) << endl;

                res.insert(v);

            } else {
                std::unordered_set<bitset < 512 >> sub = solveIt(input, v, size, depth + 1);
                //      cout << "++++++++ back to "<< depth << " " << "hyp " << toStringBs(hypoth, size) << " deep= " << depth<<" " <<endl;
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
        bool operator()(bitset < 512 > a, bitset < 512 > b)
        {   
            for(int i=a.size()-1;i>=0;i--){
                if(a[i]==true && b[i]==false) return false;
                if(a[i]==false && b[i]==true) return true;
            }
            return false;
        }   
    } customLess;
std::vector<bitset < 512 >> sortedFunctionInversion(bitset<512> input, int size) {
    std::unordered_set<bitset < 512 >> unres=solveIt(input,input,size,0);
    std::vector<bitset < 512 >> res;
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
    bitset<512> my;
    int sz = 4;
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
        std::vector<bitset < 512 >> res = sortedFunctionInversion(my, sz);

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
    bitset<512> my;
    int sz = 4;
    int val = 3;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    for (int i = val; i < val + 1; i++) {
        my = i;

        cout << toStringBs(my, sz) << " -> ";
        cout << toStringBs(applyDirectFun(my, sz), sz) << endl;
    }
    cout << "----------- END OF DIRECT --------" << endl;

    for (int i = val; i < val + 1; i++) {
        //for (int i = 0; i < 0; i++) {
        my = i;
        cout << " inverting " << toStringBs(my, sz) << endl;
        std::unordered_set<bitset < 512 >> res = solveIt(my, my, sz, 0);

        {
            int elemind = 0;
            for (const auto& elem : res) {
                cout << (elemind++) << " : " << toStringBs(elem, sz) << endl;
            }
        }

    }
}

void showSomeDisplayVariableSize() {
    testInputOutputCompareRef();
    bitset<512> my;
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

int main(int argc, char** argv) {
    cout << formula(8) << endl;
    cout << formula(4) << endl;
    //testMyFunctionWithOneManualSize();
    testMyFunctionWithDifferentManualSize();

    //testMyFunctionWithDifferentManualSize();
    //testMyFunctionWithOneManualSize

    //bitset<512> my;
    //int size = 16;

    //for (int sz = 16; sz <= size; sz++) {
    //    cout << formula(sz) << endl;
    //}

    return 0;
}

