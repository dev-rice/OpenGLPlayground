#ifndef VertexAttribute_h
#define VertexAttribute_h

#include <string>
#include <vector>

using namespace std;

class VertexAttribute {
public:
    VertexAttribute(string name, vector<float> data);

    string getName();
    int getWidth();
    vector<float>& getData();
    
private:
    string name;
    vector<float> data;
};

#endif
