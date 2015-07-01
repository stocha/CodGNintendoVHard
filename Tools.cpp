/* 
 * File:   Tools.cpp
 * Author: Jahan
 * 
 * Created on 1 juillet 2015, 13:35
 */

#include "Tools.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream> //this is where istringstream is defined

using namespace std;


Tools::Tools() {
}

Tools::Tools(const Tools& orig) {
}

Tools::~Tools() {
}

std::unique_ptr<std::istringstream> Tools::stringToStdin(){
    string inString="00000083 000000e5";
    unique_ptr<std::istringstream> res(new istringstream(inString));
    //std::istringstream sin(inString);
    return res;
}

