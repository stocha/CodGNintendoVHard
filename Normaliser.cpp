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

#include "Normalizer.h"

const int SZVEC = 64;

namespace tools{
    bitset<SZVEC> applyDirectFun(bitset<SZVEC> dat, int size) {
        bitset<SZVEC> out;
        for (int i = 0; i < size / 2; i++) {
            for (int j = 0; j < size / 2; j++) {
                out[i + j] = out[i + j]^(dat[i] & dat[j + size / 2]);
            }
        }
        return out;
    }
    
    std::string toStringBs(bitset<SZVEC> dat, int size) {
        std::string mystring =
                dat.to_string<char, std::string::traits_type, std::string::allocator_type>();

        //cout << "doublageProvisoire pour test" << endl;
        return mystring.substr(SZVEC - size, SZVEC);
    }    


    void randize(bitset<SZVEC>& r, int a, int b, int c, int d, int sz) {
        bitset<SZVEC> one = 1;
        one = a;
        r = one;
        r = r << 16;
        one = b;
        r |= one;
        r = r << 16;
        one = c;
        r |= one;
        r = r << 16;
        one = d;
        r | one;

        bitset<SZVEC> m = 1;
        one = 1;
        while (sz - 1 > 0) {
            sz = sz - 1;
            m = m << 1 | one;
        }
        //r=r&m;
    }
}

using namespace normalizerCNF;
using namespace tools;



//namespace{
    //const int SZVEC = 64;
    

void testFullDirect(int dim) {

    bool showResult = true;

    cout << "testFullDirect " << endl;
    std::unordered_set<bitset < SZVEC >> done;
    srand(0x4787599);
    bitset<SZVEC> my;
    int sz = dim;
    unsigned int val = 0x0e24FF;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    int nbNumberToTry = 3000;
    long maxValue = 1;
    for (int i = 0; i < sz - 1; i++) {
        maxValue |= maxValue << 1;
    }

    cout << "MaxValue " << maxValue << endl;
    for (int i = 0; i < maxValue; i++) {
        long rl = rand()^(((long) rand()) << 32);
        
        rl = rl % maxValue;

        //cout << " Random " << hex << rl << endl;

        if(sz <=16)
                my = rl;
        else{
            randize(my,rand(),rand(),rand(),rand(),sz);
        }        
        my=i;
        
        bitset<SZVEC> myori = my;
        my = applyDirectFun(my, sz);
            bitset<SZVEC> checkIt;
        if (done.find(my) == done.end()) {
            cout << toStringBs(myori, sz) << " Appli direct -> "<< toStringBs(my, sz) << endl;            
            
            done.insert(my);

            //cout << " from " << toStringBs(myori, sz) << " inverting " <<toStringBs(my, sz)<< endl;
            clock_t begin = clock();
            //std::unordered_set<bitset < SZVEC >> res = solveIt(my,my, sz,0);
//            std::unordered_set<bitset < SZVEC >> res = solveItV3(my, sz);
//            {
//                int elemind = 0;
//                if (showResult) for (const auto& elem : res) {
//                    checkIt=applyDirectFun(elem, sz);
//                    bool valid=(checkIt==my);
//                        cout << (elemind++) << " : " << toStringBs(elem, sz)<< " valid " << valid << endl;
//                    }
//            }
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            cout << "  { exec time " << elapsed_secs << " s " << endl;
//            if (res.find(myori) == res.end()) {
//                cout << " ERROR " << toStringBs(myori, sz) << " not found " << endl;
//            }
        }

    }
    cout << "----------- END OF testFullDirect --------" << endl;


}

bitset<SZVEC> applyFormeDirecte(bitset<SZVEC> input){
    bitset<SZVEC> res;
    
    
    return res;
}

    void formesDirectes(int sz) {
        vector<Expr> fdr = formulesDirectForSize(sz);
        for (int i = 0; i < fdr.size(); i++) {
            //cout << "------- " << i << " ----------" << endl;
            //fdr[i].debug(0);

            cout << "------- " << i << " NORMED ----------" << endl;
            fdr[i].normalizeAndOr();
            fdr[i].debug(0);
        }

    }

    void simpleForm() {
        Expr r = Expr(OR,
                Expr(AND, Expr(Var(1)), Expr(Var(2))),
                Expr(AND,
                Expr(Expr(Var(3))),
                Expr(Expr(Var(4)))
                )
                );

        r.debug(0);
        //cout << "+++++++++  FLATTEN  +++++++++" << endl;
        //r.flatten();
        //r.debug(0);    
        cout << "+++++++++  PUSH OR  +++++++++" << endl;
        r.pushor();
        r.debug(0);
        cout << "+++++++++  FLATTEN  +++++++++" << endl;
        r.flatten();
        r.debug(0);
    }
// namespace end}

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "hello forme normale" << endl;
    //simpleForm();
    formesDirectes(10);
    return 0;
}


