#ifndef VertexShader_h
#define VertexShader_h

#include "ShaderFile.hpp"

using namespace std;

class VertexShader : public ShaderFile {
public:
    VertexShader(string filename);
private:
    GLuint createShader();

};

#endif
