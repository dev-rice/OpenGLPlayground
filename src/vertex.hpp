#ifndef Vertex_h
#define Vertex_h

#include <vector>

#include "VertexAttribute.hpp"

using namespace std;

class Vertex {
public:
    Vertex(vector<VertexAttribute> vertex_attributes);

    int getWidth();
    vector<float> flatten();
private:

    void appendAttributeDataToVector(VertexAttribute& attribute, vector<float>& vertex_data);

    vector<VertexAttribute> vertex_attributes;
};

#endif
