#ifndef MeshFileParserOBJ_h
#define MeshFileParserOBJ_h

#include "MeshFileParser.hpp"

#include <fstream> // fgets
#include <stdio.h> // sscanf
#include <map>     // map
#include <array>   // array

using namespace std;

class MeshFileParserOBJ : public MeshFileParser {
public:

    MeshFileParserOBJ();

    std::vector<GLfloat> getVertexArray();
    std::vector<GLuint> getFaceArray();

    void loadMeshFromFile(string filename);
private:


};

#endif
