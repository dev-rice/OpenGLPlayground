#ifndef ShaderFile_h
#define ShaderFile_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

#include "ShaderCreator.hpp"

using namespace std;

class ShaderFile {
public:
    ShaderFile(string filename, ShaderCreator& shader_creator);
    ~ShaderFile();

    void attachTo(GLuint shader_program);
    string getErrors();
    bool hasErrors();

    void printErrors();
    GLuint getGLId();
    string getFilename();
    ShaderCreator& getShaderCreator();

private:
    void setGLId(GLuint id);
    string getFileContents(string filename);
    GLuint loadShader(string filename);

    GLuint shader_id;
    string filename;
    ShaderCreator* shader_creator;
};

#endif
