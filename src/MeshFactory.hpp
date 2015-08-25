#ifndef MeshFactory_h
#define MeshFactory_h

#include "MeshFileParserDAE.hpp"
#include "MeshFileParserOBJ.hpp"
#include "VertexSpecification.hpp"
#include "MeshData.hpp"
#include "Mesh.hpp"

class MeshFactory {
public:

    MeshFactory();

    Mesh create3DMesh(string filename);
    Mesh createFlatMesh();

private:

    MeshFileParser& getCorrectMeshFileParser(string filename);
    string getFileExtension(string filename);

    MeshFileParserOBJ mesh_file_parser_obj;
    MeshFileParserDAE mesh_file_parser_dae;
    VertexSpecification mesh_3d_vertex_specification;
    VertexSpecification flat_mesh_vertex_specification;
};

#endif
