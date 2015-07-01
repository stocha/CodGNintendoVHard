/* 
 * File:   Tools.h
 * Author: Jahan
 *
 * Created on 1 juillet 2015, 13:35
 */

#ifndef TOOLS_H
#define	TOOLS_H

#include <iostream>
#include <vector>
#include <sstream> //this is where istringstream is defined
#include <string>
#include <memory>

using namespace std;

class Tools {
public:
    Tools();
    Tools(const Tools& orig);
    virtual ~Tools();
    
    static std::unique_ptr<std::istringstream> stringToStdin(string inString );
private:

};

#endif	/* TOOLS_H */

