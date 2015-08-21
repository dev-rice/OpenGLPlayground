#include "MeshFileParser.hpp"

std::vector<GLfloat>& MeshFileParser::getVertexArray() {
    return final_vertices;
}

std::vector<GLuint>& MeshFileParser::getFaceArray() {
    return final_faces;
}

int MeshFileParser::getNumberOfElements() {
    return getFaceArray().size();
}

void MeshFileParser::clearMeshData() {
    final_vertices.clear();
    final_faces.clear();
}
