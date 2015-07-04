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
    int count=0;

    int depth = 0;

    bool debugIncr = false;
    bool debugCurrLoopState = false;
    bool debugCount=true;
    
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
            if(increment(depth,count,v,size)){  if(debugCount) cout << " COMPLEX " << count << endl;return res; }
            continue;
        }
        if (depth >= (size / 2) -1) {
            res.insert(v);
            cout << "found "<< toStringBs(v, size) << " curr compl " << count << endl;
            if(increment(depth,count,v,size)){ if(debugCount) cout << " COMPLEX " << count << endl;return res;  }
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
            if(increment(depth,count,v,size)){ if(debugCount) cout << " COMPLEX " << count << endl;return res;  }
            continue;
        }
        //+++++++++++++++ Value accepted
        { // send it to next wave of checks
            depth++;
        }



    }// Fin boucle principale

}


void randize(bitset<SZVEC>& r,int a, int b, int c, int d, int sz){
    bitset<SZVEC> one=1;
    one =a;
    r=one;
    r=r<<16;
    one =b;
    r|=one;
    r=r<<16;
    one =c;
    r|=one;
    r=r<<16;
    one =d;
    r|one;
           
    bitset<SZVEC> m=1;
    one=1;
    while(sz-1>0){
        sz=sz-1;
        m=m<<1 | one;
    }
    //r=r&m;
}

void testAndValidateMyInvertingAtRandomWithManualSize() {

    bool showResult = true;

    cout << "testAndValidateMyInvertingAtRandomWithManualSize " << endl;
    std::unordered_set<bitset < SZVEC >> done;
    srand(0x4787599F4);
    bitset<SZVEC> my;
    int sz = 48;
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
    for (int i = 0; i < nbNumberToTry; i++) {
        long rl = rand()^(((long) rand()) << 32);
        
        rl = rl % maxValue;

        //cout << " Random " << hex << rl << endl;

        if(sz <=16)
                my = rl;
        else{
            randize(my,rand(),rand(),rand(),rand(),sz);
        }        
        
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

void applyRealCase(string data){
    //string data="32\n000073af 00000000";
    //string data="16\n73af 0000";
    int size;
    bitset<SZVEC> bs;
    tie(bs,size)=toBitSet(data);
    
    cout << " from " << data << " inverting " <<toStringBs(bs, size)<< endl;
    std::vector<bitset < SZVEC >> res= sortedFunctionInversion(bs,size);
    for(int i=0;i<res.size();i++){
        toCout(res[i],size);
    }
    
    
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
        res += "|\n";
    }
  //  res += tmp[0];res += "|\n";
  //  res += tmp[size/2];res += "|\n";
  //  res += tmp[size/2 +1];res += "|\n";
  //  res += tmp[size-2];res += "|\n";


    return res;
}

int main_blnd2(int argc, char** argv) {
   // cout << formula(4) << endl;
    //cout << formula(64) << endl;
    testAndValidateMyInvertingAtRandomWithManualSize();
    //applyRealCase( "16\n000f 0000" );
    //applyRealCase( "16\n00af 0000" );
    //applyRealCase( "32\n46508fb7 6677e201");    
}
