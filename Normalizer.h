/* 
 * File:   Normalizer.h
 * Author: denis
 *
 * Created on 6 juillet 2015, 23:16
 */

#ifndef NORMALIZER_H
#define	NORMALIZER_H

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
namespace normalizerCNF {

    class Var {
    public:

        Var() {
            value = -1;
        }

        Var(int value) : value(value) {
        }
        int value;
        bool bar = false;

        void debug() {
            if (bar) cout << '!';
            cout << value;

        }
    };

    enum op {
        AND, OR, XOR, NOT, VAL, VOID
    };
    string optos[]{"&", "|", "+", "!", "", "VOID"};

    class Expr {
    public:
        op type;
        Var val;
        vector<Expr> dat;

    public:

        Expr() {
            type = VOID;
        }

        Expr(Var v) {
            type = VAL;
            val = v;
        }

        Expr(op t, Expr a) {
            type = t;
            dat.push_back(a);
        }

        Expr(op t, Expr a, Expr b) {
            if (t == NOT) {
                cerr << "NOT with two arguments ";
                exit(1);
            };
            type = t;
            dat.push_back(a);
            dat.push_back(b);
        }

        string dpad(int pad) {
            string res = "";
            for (int i = 0; i < pad; i++) res += "   ";
            return res;
        }

        void unxor() {
            if (type == XOR) {
                if (dat.size() != 2) {
                    cerr << "invariant fail XOR a deux arguments" << endl;
                }

                Expr l = dat[0];
                Expr r = dat[1];

                dat.clear();
                type = AND;
                dat.push_back(Expr(OR, l, r));
                dat.push_back(Expr(OR, Expr(NOT, l), Expr(NOT, r)));
            }
            for (int i = 0; i < dat.size(); i++) {
                dat[i].unxor();
            }
        }

        void pushnot() {
            if (type == NOT) {
                this->delMono();
                this->invertExpr();
            }
            for (int i = 0; i < dat.size(); i++) {
                dat[i].pushnot();
            }
        }

        void pushor() {
            while (pushor_rec()) {
                // cout << "debug partiel pushor"<<endl;
                // debug(0);   
                //  cout << " fin debug partiel pushor"<<endl;
            };
        }

    private:

        int exprSz() {
            if (type != VAL) return dat.size();

            return 1;
        }

        Expr& valAt(int i) {
            if ((type == VAL && i != 0) || (type != VAL && dat[i].type != VAL)) {
                cerr << " Invariant casse valeur simple only " << endl;
                exit(1);
            }
            if (type == VAL) return *this;
            return dat[i];
        }

        void flattenNodeOnly() {
            if (type != AND && type != OR && type != VAL) {
                cerr << " flatten invariant fail : invert base expr";
                exit(0);
            }

            if (type == VAL) return;
            op me = type;

            while (true) {
                int cc = -1;
                for (int i = 0; i < dat.size(); i++) {
                    if (dat[i].type == me) {
                        cc = i;
                        break;
                    }
                }

                if (cc != -1) {
                    Expr e = dat[cc];
                    dat.erase(dat.begin() + cc);
                    for (int i = 0; i < e.dat.size(); i++) {
                        dat.push_back(e.dat[i]);
                    }
                    continue;
                }

                break;
            }
        }

        void pushor2rec() {
            for (Expr e : dat) {
                pushor2rec();
            }
            flattenNodeOnly();

            if (type != OR) {
                return;
            }


            Expr andOrNode;
            andOrNode.type = AND;
            
            vector<int> sz;
            vector<int> parc;
            for(int i=0;i<dat.size();i++){
                sz.push_back(dat[i].exprSz());
                parc.push_back(0);
            }
            
            while(parc[sz.size()-1]<sz[sz.size()-1]){
                
                Expr orNode;
                orNode.type=OR;
                
                for(int i=0;i<sz.size();i++){
                    orNode.dat.push_back(dat[i].valAt(i));
                }
                andOrNode.dat.push_back(orNode);
                
                for(int i=0;true;i++){
                    parc[i]+=1;
                    if(parc[i]<sz[i]){
                        break;
                    }
                    if(i==(sz.size()-1)){
                        break;
                    }         
                    parc[i]=0;
                }
            }

            this->type=AND;
            this->dat=andOrNode.dat;
        }
    public:

        void pushor2() {
            pushor2rec();



        }

        void flatten() {
            if (type != AND && type != OR && type != VAL) {
                cerr << " flatten invariant fail : invert base expr";
                exit(0);
            }

            if (type == VAL) return;
            op me = type;

            while (true) {
                int cc = -1;
                for (int i = 0; i < dat.size(); i++) {
                    if (dat[i].type == me) {
                        cc = i;
                        break;
                    }
                }

                if (cc != -1) {
                    Expr e = dat[cc];
                    dat.erase(dat.begin() + cc);
                    for (int i = 0; i < e.dat.size(); i++) {
                        dat.push_back(e.dat[i]);
                    }
                    continue;
                }

                break;
            }

            for (int i = 0; i < dat.size(); i++) {
                dat[i].flatten();
            }
        }

        void debug(int pad) {
            if (type == VAL) {
                cout << dpad(pad);

                val.debug();
                cout << endl;
                return;
            };

            cout << dpad(pad) << optos[type] << "{" << endl;
            for (int i = 0; i < dat.size(); i++) {
                dat[i].debug(pad + 1);
            }
            cout << dpad(pad) << "}" << endl;
        }

        void normalizeAndOr() {
            this->unxor();
            this->pushnot();
            cout << "push not done " << endl;
            pushor();
            //pushor2();
            cout << "push or done " << endl;
            flatten();
        }

    private:

        bool pushor_rec() {
            if (type == VAL) return false;
            if (type == AND) {
                bool hasPushed = false;
                for (int i = 0; i < dat.size(); i++) {
                    hasPushed = hasPushed || dat[i].pushor_rec();
                }
                return hasPushed;
            };

            op me = type;

            bool hasPushed = false;

            int cc = -1;
            for (int i = 0; i < dat.size(); i++) {
                if (dat[i].type == AND) {
                    cc = i;
                    break;
                }
            }

            if (cc != -1) {
                Expr head = dat[cc];
                dat.erase(dat.begin() + cc);
                if (dat.size() == 1) {
                    delMono();
                    hasPushed = true;
                }

                Expr nth = *this;
                for (int i = 0; i < head.dat.size(); i++) {
                    Expr old = head.dat[i];
                    head.dat[i] = Expr(OR, head.dat[i], nth);
                    hasPushed = true;
                }
                copy(head);
            }



            for (int i = 0; i < dat.size(); i++) {
                hasPushed = hasPushed || dat[i].pushor_rec();
            }
            return hasPushed;
        }

    public:

        void invertExpr() {
            if (type != AND && type != OR && type != VAL && type != NOT) {
                cerr << "invariant fail : invert base expr";
                exit(0);
            }
            if (type == NOT) {
                this->delMono();
            } else if (type == AND || type == OR) {
                if (type == AND) type = OR;
                else
                    if (type == OR) type = AND;
                for (int i = 0; i < dat.size(); i++) {
                    dat[i].invertExpr();
                }
            } else if (type == VAL) {
                val.bar = !val.bar;
            }
        }

        void copy(Expr e) {
            type = e.type;
            val = e.val;
            dat = e.dat;
        }

        void delMono() {
            if (dat.size() != 1) {
                cerr << "invariant fail : del mono non mono";
                exit(0);
            }

            copy(dat[0]);
        }

    };

    vector<Expr> formulesDirectForSize(int sz) {
        vector<Expr> res(sz - 1);

        for (int i = 0; i < sz / 2; i++) {
            for (int j = 0; j < sz / 2; j++) {
                int r = i + j;
                int a = i;
                int b = j + sz / 2;

                Expr con = Expr(AND, Expr(Var(a)), Expr(Var(b)));
                if (res[r].type == VOID) {
                    res[r] = con;
                } else {
                    res[r] = Expr(XOR, res[r], con);
                }
            }
        }

        return res;
    }

    class SolverFormule {
    public:
        vector<vector<int>> discon;
        vector<vector<int>> conintrovar;
        vector<bool> input;
        int sz;
        Expr exprbit;


    private:

        static bool wayToSort(const vector<int> &i, const vector<int> &j) {
            if (i.size() < j.size())return true;
            if (i.size() > j.size())return false;

            if (i[0] > j[0])return true;
            return false;
        }
    public:

        void simplify() {
            vector<vector<int>> dsimp;
            vector<unordered_set<int>> dcheck;

            for (int i = 0; i < discon.size(); i++) {
                vector<int> csimp;
                unordered_set<int> check;
                bool kip = true;
                for (int j = 0; j < discon[i].size(); j++) {
                    int d = discon[i][j];
                    if (check.find(d) == check.end()) {
                        check.insert(d);
                        csimp.push_back(d);
                    }
                    if (check.find(-d) != check.end()) {
                        kip = false;
                        break;
                    }
                }
                if (kip && find(dcheck.begin(), dcheck.end(), check) == dcheck.end()) {
                    sort(csimp.begin(), csimp.end());
                    dsimp.push_back(csimp);
                    dcheck.push_back(check);
                }
            }
            sort(dsimp.begin(), dsimp.end(), wayToSort);
            discon = dsimp;


            unordered_set<int> hash;

            int did = 0;
            for (int i = 0; i < discon.size(); i++) {
                vector<int> v = discon[i];
                int cid = 0;
                vector<int> ntolvl;
                for (int j = 0; j < v.size(); j++) {
                    int n = getIndex(v[j]);
                    if (hash.find(n) == hash.end()) {
                        ntolvl.push_back(n);
                    }
                    hash.insert(n);
                    cid++;
                }
                conintrovar.push_back(ntolvl);
                did++;
            }
        }

    private:

        bool fullCheck(vector<bool> v) {
            bool disr = true;
            bool conjr = false;

            //  cout << " fullCheck "; debugVecbool(v); cout << endl;

            for (int dis = 0; dis < discon.size(); dis++) {
                conjr = false;
                for (int con = 0; con < discon[dis].size(); con++) {
                    int ind = getIndex(discon[dis][con]);
                    bool bar = getNeg(discon[dis][con]);
                    conjr = conjr || (bar ? !v[ind] : v[ind]);
                    //        cout << "check " << ind << "_"<<bar <<" curr="<<conjr<<endl;
                }
                disr = disr&conjr;
            }

            return disr;
        }
    public:

        void debugVecbool(vector<bool> it) {
            for (int i = 0; i < it.size(); i++) {
                cout << it[it.size() - 1 - i] ? "1" : "-";
            }
            cout << endl;
        }

        vector<vector<bool>> solveFullParcIt() {
            vector < vector<bool>> result;

            vector<bool> res(sz);
            int max = 1 << sz;
            for (int hyp = 0; hyp < max; hyp++) {
                for (int i = 0; i < sz; i++) {
                    res[i] = (((hyp >> i)&1) == 1);
                }

                if (fullCheck(res)) {
                    result.push_back(res);
                }
            }

            for (int i = 0; i < result.size(); i++) {
                //cout << "inverse " << i << " is ";
                debugVecbool(result[i]);
            }

            return result;

        }

        SolverFormule(vector<bool> input, int sz) {
            for (int i = 0; i < input.size(); i++) {
                this->input.push_back(input[i]);
            }
            this->sz = sz;
            vector<Expr> form = formulesDirectForSize(sz);
            for (int i = 0; i < form.size(); i++) {
                // form[i].normalizeAndOr();
                form[i].unxor();
            }
            for (int i = 0; i < form.size(); i++) {
                // cout << i << "/" << (form.size() - 1) << endl;
                if (input[i] == false) {
                    //form[i].debug(0);
                    form[i].invertExpr();
                }
                exprbit.dat.push_back(form[i]);
            }
            cout << "DIRECT FORMULE DONE" << endl;
            exprbit.debug(0);
            exprbit.type = AND;
            exprbit.normalizeAndOr();

            cout << "AND FORM NORMALIZED" << endl;
            exprbit.debug(0);   
            exit(0);

            for (int f = 0; f < exprbit.dat.size(); f++) {
                Expr disex = exprbit.dat[f];
                vector<int> curr;
                if (disex.type == VAL) {
                    curr.push_back(disex.val.bar ? -disex.val.value - 1 : disex.val.value + 1);
                    discon.push_back(curr);
                } else {
                    if (disex.type != OR) {
                        cerr << "conjonction not OR !" << endl;
                        exit(1);
                    }
                    for (int con = 0; con < disex.dat.size(); con++) {
                        Expr e = disex.dat[con];
                        curr.push_back(e.val.bar ? -e.val.value - 1 : e.val.value + 1);

                    }
                    discon.push_back(curr);
                }

            }
            // cout << "DIS CON FIRST FORM DONE" << endl;


        }

        bool getNeg(int v) {
            return (v < 0);
        }

        int getIndex(int v) {
            return ((v < 0) ? -v - 1 : v - 1);
        }

        debugFormule() {

            //            vector<Expr> fdr = formulesDirectForSize(sz);
            //            for (int i = 0; i < fdr.size(); i++) {
            //                cout << "------- " << i << " NORMED ----------" << endl;
            //                fdr[i].normalizeAndOr();
            //                fdr[i].debug(0);
            //            }
            //            cout << "debug formule for ";
            //            for (int i = 0; i < input.size(); i++) {
            //                cout << input[i] ? "1" : "0";
            //            }
            //            cout << endl;
            //            cout << "USED FORMULE "<<endl;
            //            exprbit.debug(0);

            for (int i = 0; i < discon.size(); i++) {
                for (int j = 0; j < discon[i].size(); j++) {
                    cout << (getNeg(discon[i][j]) ? "!" : " ") << getIndex(discon[i][j]) << "|";
                }
                cout << "( ";
                for (int j = 0; j < conintrovar[i].size(); j++) {
                    cout << conintrovar[i][j] << "|";
                }
                cout << " )" << endl;
            }
        }

    };

}



#endif	/* NORMALIZER_H */

