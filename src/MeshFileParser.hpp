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

    virtual std::vector<GLfloat> getVertexArray() = 0;
    virtual std::vector<GLuint>  getFaceArray() = 0;

protected:
    std::vector<GLfloat> final_vertices;
    std::vector<GLuint> final_faces;

};

#endif
