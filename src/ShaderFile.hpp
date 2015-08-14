#ifndef ShaderFile_h
#define ShaderFile_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

using namespace std;

class ShaderFile {
public:
    ShaderFile(string filename);
    ~ShaderFile();

    GLuint getGLId();
    void attachTo(GLuint shader_program);
    void printErrors();
    bool hasErrors();

private:
    GLuint shader_id;

protected:
    void setGLId(GLuint id);
    string getErrorLog();
    string getFileContents(string filename);
    virtual GLuint loadShader(string filename) = 0;
};

#endif
