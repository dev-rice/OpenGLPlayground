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

    void attachTo(GLuint shader_program);
    string getErrors();
    bool hasErrors();

    void printErrors();
    GLuint getGLId();
    string getFilename();

private:
    GLuint shader_id;
    string filename;

protected:
    void setGLId(GLuint id);
    string getFileContents(string filename);
    virtual GLuint loadShader(string filename) = 0;
};

#endif
