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

std::vector<bitset < 512 >> solveIt(bitset<512> input, bitset<512> hypoth, int size, int depth) {
    std::vector<bitset < 512 >> res;
    int magic[] = {0, size / 2 - 1, size / 2 , size - 1};
    
    cout << "hyp " << toStringBs(hypoth, size) << " deep= " << depth<<" ";
    cout <<"magic ";for(int i=0;i<4;i++)cout << magic[i] ;cout << endl;

    for (unsigned int i = 0; i < 16; i++) {
        bitset<512> v;
        v[magic[0] + depth] = i & 1;
        v[magic[1] + depth] = ((i >> 1) & 1);
        v[magic[2] + depth] = ((i >> 2) & 1);
        v[magic[3] + depth] = ((i >> 3) & 1);

        cout<< "v(b hyp) : " << toStringBs(v, size) << endl;
        
        for (int i = 0; i < depth; i++) {
            v[magic[0] + i] = hypoth[magic[0] + i];
            v[magic[1] + i] = hypoth[magic[1] + i];
            v[magic[2] + i] = hypoth[magic[2] + i];
            v[magic[3] + i] = hypoth[magic[3] + i];
        }
        
        cout<< "v(aft hyp) : " << toStringBs(v, size) << endl;        
        
        // check formula ....
        bool ext=input[depth];
        bool possible=false;
        cout<<"{";
        for(int i=0;i<depth+1;i++){
            int h=size/2;
            possible=possible^(v[i]&v[h+(depth-i)]);
            cout<<"("<<i<<"&"<<(h+(depth-i))<<")";
        }
        cout<<"}"<<endl;
        cout << "ext " << ext << " calc "<< possible << endl;
        if(ext==possible){
            
            if(depth >=(size/2)-1){
                cout << " adding validated " <<  toStringBs(v, size) << endl;
                res.push_back(v);
            }else{
                std::vector<bitset < 512 >> sub= solveIt(input,v,size,depth+1);
                cout << "++++++++ back to "<< depth << " " << "hyp " << toStringBs(hypoth, size) << " deep= " << depth<<" " <<endl;
                for(int sol=0;sol<sub.size();sol++){
                    res.push_back(sub[sol]);
                }
            }
        }
    }

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
    cout<< "----------- END OF DIRECT --------" <<endl;

        for (int i = 0; i < myPow(2, sz); i++) {
    //for (int i = 0; i < 0; i++) {
            my = i;
            cout << " inverting " << toStringBs(my, sz)<< endl;
            std::vector<bitset < 512 >> res=solveIt(my, my, sz, 0);
            for(int sol=0;sol<res.size();sol++){
                cout << sol << " : " << toStringBs(res[sol], sz) << endl;
            }
            
        }
}

void testMyFunctionWithOneManualSize(){
    testInputOutputCompareRef();
    bitset<512> my;
    int sz = 4;
    int val=5;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

        for (int i = val; i < val+1; i++) {
            my = i;

            cout << toStringBs(my, sz) << " -> ";
            cout << toStringBs(applyDirectFun(my, sz), sz) << endl;
        }
    cout<< "----------- END OF DIRECT --------" <<endl;

        for (int i = val; i < val+1; i++) {
    //for (int i = 0; i < 0; i++) {
            my = i;
            cout << " inverting " << toStringBs(my, sz)<< endl;
            std::vector<bitset < 512 >> res=solveIt(my, my, sz, 0);
            for(int sol=0;sol<res.size();sol++){
                cout << sol << " : " << toStringBs(res[sol], sz) << endl;
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
    cout << formula(4) << endl;    
    testMyFunctionWithOneManualSize();
    
    //testMyFunctionWithDifferentManualSize();
    //testMyFunctionWithOneManualSize
    
    //bitset<512> my;
    //int size = 16;

    //for (int sz = 16; sz <= size; sz++) {
    //    cout << formula(sz) << endl;
    //}

    return 0;
}

