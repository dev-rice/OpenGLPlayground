#ifndef MeshFileParser_h
#define MeshFileParser_h

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include <vector>
#include <string>

using namespace std;

class MeshFileParser {
public:
    MeshFileParser() {;}

    std::vector<GLfloat>& getVertexArray();
    std::vector<GLuint>& getFaceArray();
    int getNumberOfFaces();
    void clearMeshData();

    virtual void loadMeshFromFile(string filename) = 0;

protected:
    std::vector<GLfloat> final_vertices;
    std::vector<GLuint> final_faces;

};

#endif
