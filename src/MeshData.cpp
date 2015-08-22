#include "MeshData.hpp"

MeshData::MeshData(vector<GLfloat>& vertices, vector<GLuint>& elements) : vertices(&vertices), elements(&elements) {

}

vector<GLfloat>& MeshData::getVertices() {
    return *vertices;
}

vector<GLuint>& MeshData::getElements() {
    return *elements;
}
