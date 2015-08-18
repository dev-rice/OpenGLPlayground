#ifndef ShaderCreator_h
#define ShaderCreator_h

#include "includes/gl.hpp"

#include <iostream>

using namespace std;

class ShaderCreator {
public:
    ShaderCreator() {;}
    virtual GLuint create() = 0;
private:

};

#endif
