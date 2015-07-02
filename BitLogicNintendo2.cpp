/* 
 * File:   BitLogicNintendo2.cpp
 * Author: Jahan
 * 
 * Created on 2 juillet 2015, 12:02
 */

#include "BitLogicNintendo2.h"



std::unordered_set<bitset < SZVEC >> solveItV3(bitset<SZVEC> input, int size) {
    std::unordered_set<bitset < SZVEC >> res;
    bitset<SZVEC> v;
    int magic[] = {0, size / 2 - 1, size / 2, size - 1};

    int depth = 0;

    bool debugIncr = false;
    bool debugCurrLoopState = false;
    
    //std::unordered_set<bitset < SZVEC >> debugHypSeq[10];

    while (true) {
        if(debugCurrLoopState) cout << "dept " << depth << " v " <<  toStringBs(v, size) << endl;
        
        //if (debugHypSeq[depth].find(v) != debugHypSeq[depth].end()) {      
        //    cout << " ======= ERROR " << " already visited "<< "for " << depth << endl;
        //                return res;
        //}  else{
        //    debugHypSeq[depth].insert(v);
        //}

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
            cout << "found "<< toStringBs(v, size) << endl;
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


void testAndValidateMyInvertingAtRandomWithManualSize() {

    bool showResult = true;

    cout << "testAndValidateMyInvertingAtRandomWithManualSize " << endl;
    std::unordered_set<bitset < SZVEC >> done;
    srand(0x478754);
    bitset<SZVEC> my;
    int sz = 48;
    unsigned int val = 0x0e24FF;
    //cout << formula(size/2) << endl;         
    //cout << formula(size) << endl;     
    //cout << formula(size*2) << endl;

    int nbNumberToTry = 3;
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
            bitset<SZVEC> checkIt;
        if (done.find(my) == done.end()) {
            cout << toStringBs(myori, sz) << " Appli direct -> "<< toStringBs(my, sz) << endl;            
            
            done.insert(my);

            cout << " from " << toStringBs(myori, sz) << " inverting " <<toStringBs(my, sz)<< endl;
            clock_t begin = clock();
            //std::unordered_set<bitset < SZVEC >> res = solveIt(my,my, sz,0);
            std::unordered_set<bitset < SZVEC >> res = solveItV3(my, sz);
            {
                int elemind = 0;
                if (showResult) for (const auto& elem : res) {
                    checkIt=applyDirectFun(elem, sz);
                    bool valid=(checkIt==my);
                        cout << (elemind++) << " : " << toStringBs(elem, sz)<< " valid " << valid << endl;
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
    std::unordered_set<bitset < SZVEC >> unres=solveItV3(input,size);
    std::vector<bitset < SZVEC >> res;
                for (const auto& subv : unres) {
                    res.push_back(subv);
                } 
        std::sort (res.begin(), res.end(),customLess);
    return res;

}

void applyRealCase(){
    //string data="32\n000073af 00000000";
    string data="16\n73af 0000";
    int size;
    bitset<SZVEC> bs;
    tie(bs,size)=toBitSet(data);
    
    cout << " from " << data << " inverting " <<toStringBs(bs, size)<< endl;
    std::vector<bitset < SZVEC >> res= sortedFunctionInversion(bs,size);
    for(int i=0;i<res.size();i++){
        toCout(res[i],size);
    }
    
    
}

int main(int argc, char** argv) {
    testAndValidateMyInvertingAtRandomWithManualSize();
   // applyRealCase(  );
}
