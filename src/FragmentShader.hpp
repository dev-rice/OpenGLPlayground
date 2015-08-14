#ifndef FragmentShader_h
#define FragmentShader_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

using namespace std;

class FragmentShader {
public:
    FragmentShader(string filename);

    GLuint getGLId();
private:
    GLuint loadFragmentShader(string filename);
    GLuint shader_id;
    string getShaderErrorLog();
    string getFileContents(string filename);

};

#endif
