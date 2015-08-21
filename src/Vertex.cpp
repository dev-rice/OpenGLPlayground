#include "Vertex.hpp"

Vertex::Vertex(vector<VertexAttribute> vertex_attributes) : vertex_attributes(vertex_attributes) {

}

int Vertex::getWidth() {
    int width = 0;
    for(VertexAttribute& attribute : vertex_attributes) {
        width += attribute.getWidth();
    }
    return width;
}

vector<float> Vertex::flatten() {
    vector<float> flattened;

    for(VertexAttribute& attribute : vertex_attributes) {
        appendAttributeDataToVector(attribute, flattened);
    }

    return flattened;
}

void Vertex::appendAttributeDataToVector(VertexAttribute& attribute, vector<float>& vertex_data) {

    vertex_data.insert(vertex_data.end(), attribute.getData().begin(), attribute.getData().end());

}
