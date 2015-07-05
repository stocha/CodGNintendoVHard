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
        
        void debug(){
            cout << value;
        
        }
    };
    
    enum op{AND,OR,XOR,NOT,VAL,VOID};
    string optos[]{"&","|","+","!","","VOID"};
    
    class Expr{
    public :
        Expr(){
            type=VOID;
        }
        
        Expr(Var v){
            type=VAL;
            val=v;
        }
        Expr(op t,Expr a){
            type=t;
            dat.push_back(a);
        }
        
        Expr(op t, Expr a, Expr b){
            if(t==NOT) {cerr << "NOT with two arguments "; exit(1);};
            type=t;
            dat.push_back(a);
            dat.push_back(b);
        }
        
        string dpad(int pad){
            string res="";
            for(int i=0;i<pad;i++) res += "   ";
            return res;
        }
        
        void unxor(){
            if(type==XOR){
                if(dat.size()!=2){
                    cerr << "invariant fail XOR a deux arguments" << endl; 
                }
                
                Expr l=dat[0];
                Expr r=dat[1];
                
                dat.clear();
                type=AND;
                dat.push_back(Expr(OR,l,r));
                dat.push_back(Expr(OR,Expr(NOT,l),Expr(NOT,r)));
            }
            for(int i=0;i<dat.size();i++){
                dat[i].unxor();
            }
        }
        
        void pushnot(){
            
            
        }
        
        
        
        void debug(int pad){
                        if(type==VAL) {cout << dpad(pad);val.debug();cout <<endl; return;};
            
            cout << dpad(pad) << optos[type] << "{" << endl;
            for(int i=0;i<dat.size();i++){
                dat[i].debug(pad+1);
            }
            cout<< dpad(pad) << "}" << endl;
        }
        
    private :
        void invertExpr(){
            if(type!=AND && type!=OR && type!=VAL && type!=NOT) {cerr << "invariant fail : invert base expr";exit(0);}
            
            if(type==NOT){
                type=dat[0].type;
                dat=dat[0].dat;
                val=dat[0].val;
                
            }
            
            
            
        }
        
        void delMono(){
            if(dat.size()!=1) {cerr << "invariant fail : del mono non mono";exit(0);}
            
                type=dat[0].type;
                dat=dat[0].dat;
                val=dat[0].val;            
        }
        
        
    public :
        op type;
        Var val;
        vector<Expr> dat;
    };
    
    vector<Expr> formulesDirectForSize(int sz){
        vector<Expr> res(sz);
        
        for(int i=0;i<sz/2;i++){
            for(int j=0;j<sz/2;j++){
                int r=i+j;
                int a=i;
                int b=j+sz/2;
                
                Expr con=Expr(AND,Expr(Var(a)),Expr(Var(b)));
                if(res[r].type==VOID){
                    res[r]=con;
                }else{
                    res[r]=Expr(XOR,res[r],con);
                }
            }
        }
        
        return res;
    }
}

using namespace normalizerCNF;


void formesDirectes(int sz){
    vector<Expr> fdr=formulesDirectForSize(sz);
    for(int i=0;i<fdr.size();i++){
        cout << "------- " << i << " ----------" << endl;
        fdr[i].debug(0);
    }
    
}
        
void simpleForm(){
    Expr r=Expr(XOR,
            Expr(XOR,Expr(Var(1)),Expr(Var(2)) ),
            Expr(XOR,
                Expr(NOT,Expr(Var(1))),
                Expr(NOT,Expr(Var(2))) 
            )
        );
    
    r.debug(0);
    cout << "+++++++++ UNXOR +++++++++" << endl;
    r.unxor();
    
    r.debug(0);
}

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "hello forme normale"<<endl;
    simpleForm();
    //formesDirectes(8);
    return 0;
}

