#include "VertexAttribute.hpp"

VertexAttribute::VertexAttribute(string name, vector<float> data) : name(name), data(data) {
}

string VertexAttribute::getName() {
    return name;
}
int VertexAttribute::getWidth() {
    return getData().size();
}

vector<float>& VertexAttribute::getData() {
    return data;
}
