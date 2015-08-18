#ifndef FragmentShader_h
#define FragmentShader_h

#include "ShaderFile.hpp"

using namespace std;

class FragmentShader : public ShaderFile {
public:
    FragmentShader(string filename);

private:
    GLuint createShader();

};

#endif
