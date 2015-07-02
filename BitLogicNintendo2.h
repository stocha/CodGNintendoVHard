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






bool increment(int& depth,bitset < SZVEC >& v , int size){
    
    int magic[] = {0, size / 2 - 1, size / 2, size - 1};

    bool debugIncr = false; 

            bool foundIncr = false;
            while (!foundIncr) {
                if(depth<0) return true;
                // incr
                if (depth < (size / 4)) {
                    {
                        if (debugIncr) cout << " Magic for d " << depth << " is " << (magic[0] + depth) << "|" << (magic[1] - depth) << "|" << (magic[2] + depth) << "|" << (magic[3] - depth) << "|" << endl;
                        if (debugIncr) cout << "(K) increment (before)" << " depth is  " << depth << " v " << toStringBs(v, size) << endl;

                        int inc = 0;
                        inc |= v[magic[0] + depth] ? 1 : 0;
                        inc |= v[magic[1] - depth] ? 2 : 0;
                        inc |= v[magic[2] + depth] ? 4 : 0;
                        inc |= v[magic[3] - depth] ? 8 : 0;

                        inc++;
                        // Incrementation might be 0 if overflow
                        v[magic[0] + depth] = inc & 1;
                        v[magic[1] - depth] = ((inc >> 1) & 1);
                        v[magic[2] + depth] = ((inc >> 2) & 1);
                        v[magic[3] - depth] = ((inc >> 3) & 1);

                        if (debugIncr) cout << "(K) increment (after)" << " depth is  " << depth << " v " << toStringBs(v, size) << " inc compt " << inc << endl;

                        if (inc >= 16) {
                            // Depth end MAX REACH
                            depth--;
                        } else { // incr reussie
                            break;
                        }
                    } 
                }else{ // increMaxReached
                    depth--;
                }
            }    
            return false;
}


std::unordered_set<bitset < SZVEC >> solveItV2(bitset<SZVEC> input, int size) {
    std::unordered_set<bitset < SZVEC >> res;
    bitset<SZVEC> v;
    int magic[] = {0, size / 2 - 1, size / 2, size - 1};

    int depth = 0;

    bool debugIncr = false;
    bool debugCurrLoopState = false;
    
    std::unordered_set<bitset < SZVEC >> debugHypSeq[10];

    while (true) {
        if(debugCurrLoopState) cout << "dept " << depth << " v " <<  toStringBs(v, size) << endl;
        
        if (debugHypSeq[depth].find(v) != debugHypSeq[depth].end()) {      
            cout << " ======= ERROR " << " already visited "<< "for " << depth << endl;
                        return res;
        }  else{
            debugHypSeq[depth].insert(v);
        }

        // ++++++++++++++++ Left formula on current Hyp
        //+++++++++++++
        // check formula .... left
        bool ext = input[0 + depth];
        bool possible = false;
        for (int i = 0; i < depth + 1; i++) {
            int h = size / 2;
            int riand = i;
            int rilef = h + (depth - i);
            possible = possible^(v[riand] & v[rilef]);
        }
        if (possible != ext) // reject value
        {
            if(increment(depth,v,size)) return res;
            continue;
        }
        if (depth >= (size / 2) -1) {
            res.insert(v);
            if(increment(depth,v,size)) return res;
        }     
        // ++++++++++++++++++++ Right formula on current Hyp
        //+++++++++++++++
        // check formula .... right
        int rightEdge = size - 1;
        ext = input[size - 2 - depth]; // cout << "Extern bit " << " (" <<(size-2-depth) <<") is " << input[size-2-depth] <<endl;
        possible = false;
        for (int i = 0; i < depth + 1; i++) {
            int h = size / 2;
            int riand = h - i - 1;
            int rilef = rightEdge - depth + i;
            possible = possible^(v[riand] & v[rilef]);
        }
        if (possible != ext) // reject value
        {
            if(increment(depth,v,size)) return res;
            continue;
        }
        //+++++++++++++++ Value accepted
        { // send it to next wave of checks
            depth++;
        }



    }// Fin boucle principale

}

std::unordered_set<bitset < SZVEC >> solveIt(bitset<SZVEC> input, bitset<SZVEC> hypoth, int size, int depth) {
    std::unordered_set<bitset < SZVEC >> res;
    int magic[] = {0, size / 2 - 1, size / 2, size - 1};

    bool activCond = false;
    bool activate_formul_debug = false;
    unsigned long valHypActDebug = 41;

    if (activCond)if (depth == 0) activate_formul_debug = true;

    if (activate_formul_debug)
        cout << "hyp " << toStringBs(hypoth, size) << " deep= " << depth << " ";
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

        if (activCond) if (depth >= 1 && v == valHypActDebug) activate_formul_debug = true;
        if (activate_formul_debug)
            cout << "--- depth " << depth << " v(aft hyp) : " << toStringBs(v, size) << endl;

        // check formula .... left
        bool ext = input[0 + depth];
        bool possible = false;
        if (activate_formul_debug) cout << "{";
        for (int i = 0; i < depth + 1; i++) {
            int h = size / 2;
            int riand = i;
            int rilef = h + (depth - i);
            possible = possible^(v[riand] & v[rilef]);
            if (activate_formul_debug) cout << "(" << (riand) << "&" << (rilef) << ")" << v[riand] << "&" << v[rilef];
        }
        if (activate_formul_debug) cout << "}" << endl;
        // cout << "ext " << ext << " calc "<< possible << endl;
        bool rightFormulaIsPassed = false;

        if (depth >= (size / 2) - 1) {
            rightFormulaIsPassed = (ext == possible);
        } else
            if (ext == possible) {
            // check formula .... right
            if (activate_formul_debug) cout << " check right formula part inputIs(" << toStringBs(input, size) << ") " << endl;
            int rightEdge = size - 1;
            ext = input[size - 2 - depth]; // cout << "Extern bit " << " (" <<(size-2-depth) <<") is " << input[size-2-depth] <<endl;
            possible = false;
            if (activate_formul_debug) cout << "right {";
            for (int i = 0; i < depth + 1; i++) {
                int h = size / 2;
                int riand = h - i - 1;
                int rilef = rightEdge - depth + i;
                possible = possible^(v[riand] & v[rilef]);
                if (activate_formul_debug) cout << "(" << (riand) << "&" << (rilef) << ")" << v[riand] << "&" << v[rilef];
            }
            if (activate_formul_debug) cout << "}" << endl;

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
                if (activate_formul_debug) cout << "++++++++ back to " << depth << " " << "hyp " << toStringBs(hypoth, size) << " deep= " << depth << " " << endl;
                for (const auto& subv : sub) {
                    res.insert(subv);
                    /* ... process elem ... */
                }
            }
        }
    } // fin parcours hypotheses

    return res;
}

#endif	/* BITLOGICNINTENDO2_H */

