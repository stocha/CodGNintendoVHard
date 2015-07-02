/* 
 * File:   BitLogicNintendo2.cpp
 * Author: Jahan
 * 
 * Created on 2 juillet 2015, 12:02
 */

#include "BitLogicNintendo2.h"


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
    bool debugCurrLoopState = true;
    
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
        }
        //+++++++++++++++ Value accepted
        if (depth >= (size / 2) - 1) {
            res.insert(v);
        }
        if(increment(depth,v,size)) return res;


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

void testAndValidateMyInvertingAtRandomWithManualSize() {

    bool showResult = true;

    cout << "testAndValidateMyInvertingAtRandomWithManualSize " << endl;
    std::unordered_set<bitset < SZVEC >> done;
    srand(0x478754);
    bitset<SZVEC> my;
    int sz = 8;
    unsigned int val = 0x0e24;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    int nbNumberToTry = 10;
    long maxValue = 1;
    for (int i = 0; i < sz - 1; i++) {
        maxValue |= maxValue << 1;
    }

    cout << "MaxValue " << maxValue << endl;
    for (int i = 0; i < nbNumberToTry; i++) {
        long rl = rand()^(((long) rand()) << 32);
        rl = rl % maxValue;
        //cout << " Random " << hex << rl << endl;
        my = rl;
        bitset<SZVEC> myori = my;
        my = applyDirectFun(my, sz);

        if (done.find(my) == done.end()) {
            cout << toStringBs(myori, sz) << " Appli direct -> "<< toStringBs(my, sz) << endl;            
            
            done.insert(my);

            cout << " from " << toStringBs(myori, sz) << " inverting " <<toStringBs(my, sz)<< endl;
            clock_t begin = clock();
            std::unordered_set<bitset < SZVEC >> res = solveItV2(my, sz);
            {
                int elemind = 0;
                if (showResult) for (const auto& elem : res) {
                        cout << (elemind++) << " : " << toStringBs(elem, sz) << endl;
                    }
            }
            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            cout << "  { exec time " << elapsed_secs << " s " << endl;
            if (res.find(myori) == res.end()) {
                cout << " ERROR " << toStringBs(myori, sz) << " not found " << endl;
            }
        }

    }
    cout << "----------- END OF testAndValidateMyInvertingAtRandomWithManualSize --------" << endl;


}

int main(int argc, char** argv) {
    testAndValidateMyInvertingAtRandomWithManualSize();
}
