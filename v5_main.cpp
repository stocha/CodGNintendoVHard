/* 
 * File:   v5_main.cpp
 * Author: denis
 *
 * Created on 9 juillet 2015, 19:00
 */

#include <cstdlib>
#include "v5_Formulaz.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "V5" << endl;
    //SoluSimp ss(32);
    //ss.debug_coef();
    
    FormulazTests::testAll();
    return 0;
}

