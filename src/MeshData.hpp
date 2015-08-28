#ifndef MeshData_h
#define MeshData_h

#include <vector>

#include "includes/gl.hpp"

using namespace std;

class MeshData {
public:
    MeshData(vector<GLfloat>& vertices, vector<GLuint>& elements);

    vector<GLfloat>& getVertices();
    vector<GLuint>& getElements();

private:
    vector<GLfloat>& vertices;
    vector<GLuint>& elements;

};

#endif
