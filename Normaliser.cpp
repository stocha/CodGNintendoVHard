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
namespace normalizerCNF{
    class Var{
    public :
        Var(){
            value=-1;
        }
        Var(int value) : value(value){
        }        
        int value;
    };
    
    enum class op{AND,OR,XOR,NOT,VAL};
    
    class Expr{
    public :
        Expr(Var v){
            type=op::VAL;
            val=v;
        }
        Expr(op t,Expr a){
            type=t;
            dat.push_back(a);
        }
        
        Expr(op t, Expr a, Expr b){
            if(t==op::NOT) {cerr << "NOT with two arguments "; exit(1);};
            type=t;
            dat.push_back(a);
            dat.push_back(b);
        }
        
    public :
        op type;
        Var val;
        vector<Expr> dat;
    };
    
}
        
     

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "hello forme normale";
    return 0;
}

