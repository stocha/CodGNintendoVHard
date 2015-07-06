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

using namespace normalizerCNF;

namespace {
    const int SZVEC = 64;

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
}

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "hello forme normale" << endl;
    //simpleForm();
    formesDirectes(10);
    return 0;
}


