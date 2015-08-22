// mesh_file_parser.h
// Header file for *.obj file importing
// and mesh object creation
// Trevor Westphal
#ifndef MeshFileParserDAE_h
#define MeshFileParserDAE_h

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "MeshFileParser.hpp"

#include <cmath>
#include <algorithm>
#include <map>

#include "pugixml.hpp" // PUGI xml library
#include "vertex.hpp"

using namespace std;

class MeshFileParserDAE : public MeshFileParser {
public:
    MeshFileParserDAE();

    void loadMeshFromFile(string filename);

private:
    void writeFinalArrays(std::vector<Vertex>&, std::vector<GLuint>&);
    void calculateTangentsAndBinormals(std::vector<Vertex>&, std::vector<GLuint>&);
    bool getVerticesAndElements(pugi::xml_node, std::vector<Vertex>&, std::vector<GLuint>&);

    std::vector<Vertex> unique_vertices;
    std::map<int, int> vertex_to_unique;

    string filename;

    bool flat_shading;
};

#endif
