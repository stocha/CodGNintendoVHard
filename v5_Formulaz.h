/* 
 * File:   Formulaz.h
 * Author: denis
 *
 * Created on 9 juillet 2015, 19:01
 */

#ifndef FORMULAZ_H
#define	FORMULAZ_H

#include <cstdlib>
#include <iomanip>
#include <bitset>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <iostream>
#include <sstream> //this is where istringstream is defined
#include <string>
#include <memory>
using namespace std;

class SoluSimp {
    int sz;

public:

    SoluSimp(int sz) {
        this->sz = sz;
    }
public:

    int nbXor(int at) {
        //if(at>=sz/2) return 0;
        int d = (sz - 1) / 2 - at;
        if (d >= 0) return ((sz / 2 - 1) - d + 1);
        cout << "ERROR " << at << " out of formbounds";
        exit(1);
        return 0;
    }

    int coefL(int at, int num) {
        return (at - num);
    }

    int coefLsec(int at, int num) {
        return sz / 2 - 1 + num - at;
    }

    int coefR(int at, int num) {
        return num + sz / 2;
    }

    int coefRsec(int at, int num) {
        return sz / 2 - 1 - num + sz / 2;
    }

    void debug_coef() {

        const int fillnb = 2;
        for (int i = 0; i < sz / 2; i++) {
            cout << setfill('0') << setw(3) << i << " :: ";
            for (int j = 0; j < nbXor(i); j++) {
                cout << setfill('0') << "(" << setw(fillnb) << coefL(i, j) << "&" << setw(fillnb) << coefR(i, j) << ")+";
            }
            cout << " & " << endl;

            if (i + 1 == sz / 2) break;
            cout << setfill('0') << setw(3) << i << " :: ";
            for (int j = 0; j < nbXor(i); j++) {
                cout << setfill('0') << "(" << setw(fillnb) << coefLsec(i, j) << "&" << setw(fillnb) << coefRsec(i, j) << ")+";
            }
            cout << " & " << endl;
        }
        //        for(int i=0;i<sz/2 -1;i++){
        //            cout << i << " :: ";
        //            for(int j=0;j<nbXor(i);j++){
        //                cout << "(" << coefLsec(i,j) << "&" << coefRsec(i,j) << ")+";
        //            }
        //            cout<<" & "<<endl;
        //        }        

    }
};

class bitField {
private:
    bitset<512> dat;
    int sz;
public:

    bitField(int startSz) : sz(startSz) {
    }

    bitField(string strHex) {
        istringstream in(strHex);
        int size = 0;
        in >> size;
        unsigned int a[size / 16];
        bitset<32> ab[size / 16];
        for (int i = 0; i < size / 16; i++) {
            in >> hex >> a[i];
            ab[i] = bitset<32>(a[i]);
        }

        for (int i = 0; i < size * 2; i++) {
            int dec = i / 32;
            int ind = i % 32;
            dat[i] = ab[dec][ind];
        }
        sz = size * 2;
    }

    bitField& operator++() // prefix ++
    {
        for (int i = 0; i < size(); i++) {
            if ((*this)[i] == 0) {
                set(i, 1);
                return *this;
            }
            set(i, 0);
        }
        return *this;
    }

    void incSymetric() // prefix ++
    {
        if (!isSymetric()) {
            ++(*this);
            return;
        }

        int s = size() / 2;
        for (int i = s; i < size(); i++) {
            if ((*this)[i] == 0) {
                set(i, 1);


                for (int i = 0; i < s; i++) { // mise a 0
                    set(i, 0);
                }
                return;
            }
            set(i, 0);
        }

        for (int i = 0; i < s; i++) {
            set(i, 0);
        }
    }

    bool isSymetric() {
        bool res = true;
        int s = size() / 2;
        for (int i = 0; i < s; i++) {
            if ((*this)[i] != (*this)[i + s]) {
                return false;
            }
        }

        return res;
    }

    bitField& swap() {
        int s = size() / 2;
        for (int i = 0; i < s; i++) {
            int l = (*this)[i + s];
            set((i + s), (*this)[i]);
            set((i), l);
        }
        return *this;
    }

    bitField& incAt(int at) // prefix ++
    {
        for (int i = at; i < size(); i++) {
            if ((*this)[i] == 0) {
                set(i, 1);
                return *this;
            }
            set(i, 0);
        }
        return *this;
    }

    bool operator==(const bitField& other) {
        bool res = other.sz == sz;
        if (!res) return res;
        for (int i = 0; i < sz; i++) {
            if ((*this)[i] != other[i]) return false;
        }
        return res;
    }

    bool isZero() {
        for (int i = 0; i < size(); i++) {
            if ((*this)[i] != 0) {
                return false;
            }
        }
        return true;
    }

    long operator[](std::size_t pos) const {
        return dat[pos] ? 1 : 0;
    }

    void set(std::size_t at, long value) {
        dat[at] = value;
    }

    int size() {
        return sz;
    }

    void randomize() {
        for (int i = 0; i < size(); i++) {
            set(i, rand() % 2);
        }
    }

    void clear() {
        for (int i = 0; i < size(); i++) {
            set(i, 0);
        }
    }

    string str() {
        std::ostringstream sout;
        unsigned int a [sz / 32];
        //bitset<32> ab[sz / 32];
        for (int i = sz - 1; i >= 0; --i) {
            sout << (dat[i] ? '1' : '0'); // print result    
            if (i % 4 == 0) sout << ".";
            if (i % 8 == 0) sout << " ";
        }

        string res = sout.str();
        return res;


    }

    string strHex() {

        std::ostringstream sout;
        int nb = sz / 32;
        if (sz % 32 != 0) nb += 1;
        unsigned int a [nb];
        bitset<32> ab[nb];
        for (int i = 0; i < sz; i++) {
            int dec = i / 32;
            int ind = i % 32;
            ab[dec][ind] = dat[i];
        }
        for (int i = 0; i < (nb); i++)
            sout << setfill('0') << setw(8) << hex << ab[i].to_ulong() << " "; // print result       

        return sout.str();
    }


};

class varEqField {
    int v[512 + 2];
    int sz;
    bitset<512> neg;

    int ea;
    int eb;

    int fa;
    int fb;

    bool partsign = false;
    int nbImpure = 0;
public:

    void cp(varEqField src) {
        for (int i = 0; i < sz + 2; i++) {
            v[i] = src.v[i];
            neg[i] = src.neg[i];
        }
    }

    int firstFreeVariable() {
        for (int i = 0; i < sz; i++) {

            if (get(i) >= 0)
                return i;
        }
        return -1;
    }

    string str() {
        std::ostringstream sout;
        for (int i = 0; i < sz; i++) {

            if (getsign(i)) sout << "!";
            sout << get(i) << "|";
        }
        sout << endl;


        string res = sout.str();
        return res;
    }

    void prepare() {
        partsign = false;
        nbImpure = 0;
    }

    void push(int a, int b) {

        bool pure = get(a) < 0 && get(b) < 0;
        if (pure) {
            if (get(a) != get(b)) {

            } else {
                bool ab = getAsBool(get(a));
                partsign = (partsign != ab);
            }
        } else if (get(a) == get(b) && (getsign(a) != getsign(b))) {

        } else {
            ea = fa;
            eb = fb;

            fa = get(a);
            fb = get(b);

            if (fa == fb) {
                fb = -1;
            }

            if (fa < 0) {
                int sw = fa;
                fa = fb;
                fb = sw;
            }

            nbImpure++;

            //   cout <<"fa " << fa<<endl;
            //   cout << "fb "<< fb<<endl;            
        }
    }

    int sign(bool sign) {
        int res=0;
        partsign = (partsign != sign);

        if (nbImpure == 0) {
            if(partsign!=sign) return -1;
        }
        if (nbImpure == 1) {
            if (fa >= 0 && fb >= 0 && partsign) {
                this->setVarEquivalenceAEqB(fa, -1, false);
                this->setVarEquivalenceAEqB(fb, -1, false);
                res++;
            } else
                if (fb == -1) {
                this->setVarEquivalenceAEqB(fa, partsign ? -2 : -1, false);
                //  cout << " 1 impure " << fa << " <- " << (partsign ? -2 : -1) << endl;
                res++;
            }
        }
        if (nbImpure == 2) {
            if (fb < 0) {
                if (eb < 0) {
                    this->setVarEquivalenceAEqB(fa, ea, partsign);
                    res++;
                }

            }

        }
        return res;
    }

private:

    void p(int dst) {

    }
public:

    bool getAsBool(int i) {
        if (i == -2) false;
        else true;
    }

    varEqField(int sz) {
        this->sz = sz;
        for (int i = 0; i < sz + 2; i++) {
            v[i] = i;
            neg[i] = false;
        }
    }

    long get(std::size_t pos) {
        int curr = pos + 2;
        int next = v[pos + 2];
        bool a = neg[curr];

        while (next != curr) {

            //        v[curr]=v[next];
            curr = next;
            a = (a != neg[next]);

            next = v[next];
        }

        v[curr] = v[next];
        neg[curr] = a;

        curr = pos + 2;
        if (v[next] == 0 && neg[curr]) {
            v[curr] = 1;
            neg[curr] = false;
        }

        //  cout << v[next] << " " << neg[curr]<<endl;
        if (v[next] == 1 && neg[curr]) {
            // cout << "detected -1 neg " << endl;
            v[curr] = 0;
            neg[curr] = false;
        }

        return v[next] - 2;
    }

    bool getsign(std::size_t pos) {
        int g = get(pos);
        return neg[pos + 2];
    }

    void setVarEquivalenceAEqB(int a, int b, bool s) {


        int ca = get(a);
        int cb = get(b);

        //  cout << "" << ca << "==" << cb<< " whith " << s <<endl;

        int i, j;
        if (ca > cb) {
            j = ca;
            i = cb;
        } else {
            i = ca, j = cb; // i<j
        }

        if (j >= 0) {
            v[j + 2] = v[i + 2];
            bool ph = (getsign(j) != getsign(i));
            neg[j + 2] = (ph != s);
        }
    }


};

bitField applyEncode(bitField in);

class inverterInterface {
public:
    virtual vector<bitField> invert(bitField in) = 0;
};

class refInvert : public inverterInterface {
public:

    vector<bitField> invert(bitField in) {
        vector<bitField> resvv;

        bitField res(in.size());


        while (true) {

            if (applyEncode(res) == in) {
                //cout << res.str() << " is solution " << endl;
                resvv.push_back(res);
            }

            ++res;
            if (res.isZero()) break;
        }


        return resvv;
    }
};

class seqInvert : public inverterInterface {
public:

    vector<bitField> invert(bitField in) {

        //cout << "seqInvert " << endl;

        SoluSimp ss(in.size());
        vector<bitField> resvv;

        if (in[in.size() - 1] == 1) return resvv;

        bitField res(in.size());
        res.clear();

        const int halfSize = in.size() / 2;
        int depth = 0;
        while (true) {

            // cout << "CHECK " << res.str() << " against " << in.str() << " depth " << depth << " half " << halfSize << endl;

            long v = in[depth];

            if (depth < halfSize) {
                //cout << "depth " << depth <<" nbXor "<< ss.nbXor(depth)<< endl;
                for (int i = 0; i < ss.nbXor(depth); i++) {
                    //  cout << v << " ^= " << res[ss.coefL(depth,i)] << " & " << res[ss.coefR(depth,i)]<< endl;
                    //cout << "addr" << depth << " ^= " << ss.coefL(depth,i) << " & " << ss.coefR(depth,i)<< endl;
                    v ^= (res[ss.coefL(depth, i)] & res[ss.coefR(depth, i)]);
                }
            } else {
                int ndDepth = in.size() - depth - 2;
                //cout << "depth " << depth << " ndDepth " << ndDepth << " nbXor ";
                //cout << ss.nbXor(ndDepth)<< endl;
                for (int i = 0; i < ss.nbXor(ndDepth); i++) {
                    //  cout << v << " ^= " << res[ss.coefLsec(ndDepth,i)] << " & " << res[ss.coefRsec(ndDepth,i)]<< endl;
                    //cout << "addr" << depth << " ^= " << ss.coefLsec(ndDepth,i) << " & " << ss.coefRsec(ndDepth,i)<< endl;
                    v ^= (res[ss.coefLsec(ndDepth, i)] & res[ss.coefRsec(ndDepth, i)]);
                }
            }
            if (v != 0) {
                ++res;
                depth = 0;
                //cout << "next res" << res.str() << endl;
                if (res.isZero()) {

                    break;
                }
                continue;
            }
            //cout << "PASSED " << depth << endl;

            depth++;
            if (!(depth < in.size() - 1)) {
                //cout << "Depth end : " << depth << endl;
                depth = 0;
                resvv.push_back(res);
                ++res;
                if (res.isZero()) break;
            }

        }


        return resvv;
    }
};

class eq01Invert : public inverterInterface {
public:

    varEqField transf(varEqField question, bitField in) {
        varEqField root(in.size());
        root.cp(question);
        cout << "input" << root.str() << endl;
        SoluSimp ss(in.size());

        const int halfSize = in.size() / 2;
        for (int depth = 0; depth < in.size(); depth++) {
            long v = in[depth];

            root.prepare();
            if (depth < halfSize) {
                //cout << "depth " << depth <<" nbXor "<< ss.nbXor(depth)<< endl;
                for (int i = 0; i < ss.nbXor(depth); i++) {
                    //  cout << v << " ^= " << res[ss.coefL(depth,i)] << " & " << res[ss.coefR(depth,i)]<< endl;
                    //cout << "addr" << depth << " ^= " << ss.coefL(depth,i) << " & " << ss.coefR(depth,i)<< endl;
//                    v ^= (res[ss.coefL(depth, i)] & res[ss.coefR(depth, i)]);
                    root.push(ss.coefL(depth, i), ss.coefR(depth, i));
                }
                root.sign(in[depth]);
            } else {
                int ndDepth = in.size() - depth - 2;
                //cout << "depth " << depth << " ndDepth " << ndDepth << " nbXor ";
                //cout << ss.nbXor(ndDepth)<< endl;
                for (int i = 0; i < ss.nbXor(ndDepth); i++) {
                    //  cout << v << " ^= " << res[ss.coefLsec(ndDepth,i)] << " & " << res[ss.coefRsec(ndDepth,i)]<< endl;
                    //cout << "addr" << depth << " ^= " << ss.coefLsec(ndDepth,i) << " & " << ss.coefRsec(ndDepth,i)<< endl;
             //       v ^= (res[ss.coefLsec(ndDepth, i)] & res[ss.coefRsec(ndDepth, i)]);
                    root.push(ss.coefL(depth, i), ss.coefR(depth, i));
                }
                root.sign(in[depth]);
            }

        }
        int firstFree=root.firstFreeVariable();
        
        
        if(firstFree==-1){
            cout << "found " << root.str() << endl;
            return root; 
        }
        else{
            cout << "after deduction " << root.str() << endl;
            cout << "first free variable is " << firstFree << endl;
            root.setVarEquivalenceAEqB(0,firstFree,false);
            varEqField left=transf(root,in);
                    
            root.setVarEquivalenceAEqB(1,firstFree,false);                    
            varEqField right=transf(root,in);
                    
            if(left.firstFreeVariable()==-1){
                return left;
            }
            if(right.firstFreeVariable()==-1){
                return right;
            }   
            return root;
        }
    }

    vector<bitField> invert(bitField in) {

        varEqField root(in.size());
        varEqField answer = transf(root, in);

        cout << answer.str() << endl;

        //cout << "seqInvert " << endl;

        SoluSimp ss(in.size());
        vector<bitField> resvv;

        if (in[in.size() - 1] == 1) return resvv;

        bitField res(in.size());
        res.clear();

        const int halfSize = in.size() / 2;
        int depth = 0;
        while (true) {

            // cout << "CHECK " << res.str() << " against " << in.str() << " depth " << depth << " half " << halfSize << endl;

            long v = in[depth];

            if (depth < halfSize) {
                //cout << "depth " << depth <<" nbXor "<< ss.nbXor(depth)<< endl;
                for (int i = 0; i < ss.nbXor(depth); i++) {
                    //  cout << v << " ^= " << res[ss.coefL(depth,i)] << " & " << res[ss.coefR(depth,i)]<< endl;
                    //cout << "addr" << depth << " ^= " << ss.coefL(depth,i) << " & " << ss.coefR(depth,i)<< endl;
                    v ^= (res[ss.coefL(depth, i)] & res[ss.coefR(depth, i)]);
                }
            } else {
                int ndDepth = in.size() - depth - 2;
                //cout << "depth " << depth << " ndDepth " << ndDepth << " nbXor ";
                //cout << ss.nbXor(ndDepth)<< endl;
                for (int i = 0; i < ss.nbXor(ndDepth); i++) {
                    //  cout << v << " ^= " << res[ss.coefLsec(ndDepth,i)] << " & " << res[ss.coefRsec(ndDepth,i)]<< endl;
                    //cout << "addr" << depth << " ^= " << ss.coefLsec(ndDepth,i) << " & " << ss.coefRsec(ndDepth,i)<< endl;
                    v ^= (res[ss.coefLsec(ndDepth, i)] & res[ss.coefRsec(ndDepth, i)]);
                }
            }
            if (v != 0) {
                ++res;
                depth = 0;
                //cout << "next res" << res.str() << endl;
                if (res.isZero()) {

                    break;
                }
                continue;
            }
            //cout << "PASSED " << depth << endl;

            depth++;
            if (!(depth < in.size() - 1)) {
                //cout << "Depth end : " << depth << endl;
                depth = 0;
                resvv.push_back(res);
                ++res;
                if (res.isZero()) break;
            }

        }


        return resvv;
    }
};

class seqInvertSimetric : public inverterInterface {
public:

    vector<bitField> invert(bitField in);
};

class compareImpl {
    inverterInterface *a;
    inverterInterface *b;
public:

    compareImpl(inverterInterface *a, inverterInterface *b) : a(a), b(b) {

    }

    void compareThem(int bitSz, int nbNum) {

        clock_t start = clock();


        bitField bf(bitSz);
        for (int essai = 0; essai < nbNum; essai++) {
            bf.randomize();
            cout << "test " << bf.strHex() << " / " << bf.str() << endl;

            auto ra = a->invert(bf);
            auto rb = b->invert(bf);


            bool eq = true;

            if (ra.size() == rb.size()) {
                cout << " nb result " << ra.size() << endl;

                for (int i = 0; i < ra.size(); i++) {
                    if (!(ra[i] == rb[i])) {
                        eq = false;
                        break;
                    }
                }
            } else {
                eq = false;
            }




            if (!eq) {
                cout << "ERROR for " << bf.str() << endl;
                cout << "---------- RA SOL" << endl;
                for (auto e : ra) {
                    cout << e.str() << "|" << endl;
                }
                cout << "---------- RB SOL" << endl;
                for (auto e : rb) {
                    cout << e.str() << "|" << endl;
                }
                cout << "----------" << endl;
                exit(1);
            }

        }

        clock_t end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        cout << " time spent for " << bitSz << " bit and " << nbNum << " values is " << time << endl;
        if (time > 0) {
            cout << "" << nbNum / time << " inst per second " << endl;
        }
    }

};

class FormulazTests {
public:
    static void testBitField();
    static void testInvertRef();
    static void testAll();

};


#endif	/* FORMULAZ_H */

