#ifndef VertexShader_h
#define VertexShader_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

using namespace std;

class VertexShader {
public:
    VertexShader(string filename);

    GLuint getGLId();
private:
    GLuint loadVertexShader(string filename);
    GLuint shader_id;
    string getShaderErrorLog();
    string getFileContents(string filename);
};

#endif
