#include "MeshFactory.hpp"

MeshFactory::MeshFactory() {
    mesh_3d_vertex_specification.addAttribute(VertexAttribute("position", 3, 0));
    mesh_3d_vertex_specification.addAttribute(VertexAttribute("normal", 3, 3));
    mesh_3d_vertex_specification.addAttribute(VertexAttribute("texture_coordinates", 2, 6));

    flat_mesh_vertex_specification.addAttribute(VertexAttribute("position", 2, 0));
    flat_mesh_vertex_specification.addAttribute(VertexAttribute("texture_coordinates", 2, 2));
}

// On most compilers this is not actually as bad as it looks, see
// https://en.wikipedia.org/wiki/Return_value_optimization
Mesh MeshFactory::create3DMesh(string filename) {
    MeshFileParser& parser = getCorrectMeshFileParser(filename);
    parser.loadMeshFromFile(filename);
    MeshData data(parser.getVertexArray(), parser.getFaceArray());
    Mesh mesh(data, mesh_3d_vertex_specification);
    return mesh;
}

MeshFileParser& MeshFactory::getCorrectMeshFileParser(string filename) {
    string extension = getFileExtension(filename);
    if (extension == ".obj") {
        return mesh_file_parser_obj;
    } else if (extension == ".dae") {
        return mesh_file_parser_dae;
    }
}

string MeshFactory::getFileExtension(string filename) {
    return filename.substr(filename.size() - 4);
}

Mesh MeshFactory::createFlatMesh() {
    vector<GLfloat> vertices = {
             -1.0f,  1.0f,  0.0f, 1.0f,
             -1.0f, -1.0f,  0.0f, 0.0f,
              1.0f,  1.0f,  1.0f, 1.0f,
              1.0f, -1.0f,  1.0f, 0.0f,

    };

    vector<GLuint> elements = {
            0, 1, 2,
            1, 3, 2,
    };

    MeshData flat_mesh_data(vertices, elements);
    Mesh flat_mesh(flat_mesh_data, flat_mesh_vertex_specification);
    return flat_mesh;
}
