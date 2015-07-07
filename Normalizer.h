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
#include <vector>
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
                //cout << "debug partiel pushor"<<endl;
                // debug(0);   
                //  cout << " fin debug partiel pushor"<<endl;
            };
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
            pushor();
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
                hasPushed = true;
                Expr head = dat[cc];
                dat.erase(dat.begin() + cc);
                if (dat.size() == 1) {
                    delMono();

                }

                Expr nth = *this;
                for (int i = 0; i < head.dat.size(); i++) {
                    Expr old = head.dat[i];
                    head.dat[i] = Expr(OR, head.dat[i], nth);
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

        SolverFormule(vector<bool> input, int sz) {
            for (int i = 0; i < input.size(); i++) {
                this->input.push_back(input[i]);
            }
            this->sz = sz;
            vector<Expr> form = formulesDirectForSize(sz);
            for (int i = 0; i < form.size(); i++) {
                form[i].normalizeAndOr();
            }

            for (int i = 0; i < form.size(); i++) {
                if (input[i] == false) {
                    form[i].invertExpr();
                    form[i].normalizeAndOr();
                }
                exprbit.dat.push_back(form[i]);
            }
            exprbit.type=AND;

            for (int f = 0; f < form.size(); f++) {
                for (int dis = 0; dis < form[f].dat.size(); dis++) {
                    vector<int> curr;
                    for (int con = 0; con < form[f].dat[dis].dat.size(); con++) {
                        Expr e = form[f].dat[dis].dat[con];
                        curr.push_back(e.val.bar ? -e.val.value : e.val.value);

                    }
                    discon.push_back(curr);
                }

            }

            unordered_set<int> hash;

            int did = 0;
            for (vector<int> v : discon) {
                int cid = 0;
                vector<int> ntolvl;
                for (int n : v) {
                    if (hash.find(n) != hash.end()) {
                        ntolvl.push_back(n);
                    }
                    hash.insert(n);
                    cid++;
                }
                conintrovar.push_back(ntolvl);
                did++;
            }
        }

        debugFormule() {

            vector<Expr> fdr = formulesDirectForSize(sz);
            for (int i = 0; i < fdr.size(); i++) {
                cout << "------- " << i << " NORMED ----------" << endl;
                fdr[i].normalizeAndOr();
                fdr[i].debug(0);
            }
            cout << "debug formule for ";
            for (int i = 0; i < input.size(); i++) {
                cout << input[i] ? "1" : "0";
            }
            cout << endl;
            cout << "USED FORMULE "<<endl;
            exprbit.debug(0);

            for (int i = 0; i < discon.size(); i++) {
                for (int j = 0; j < discon[i].size(); j++) {
                    cout << discon[i][j] << "|";
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

