#include "MeshFactory.hpp"

Mesh MeshFactory::createMesh(string filename) {
    return Mesh(filename, getCorrectParser(filename));
}

MeshFileParser& MeshFactory::getCorrectParser(string filename) {
    string file_extension = lastCharacters(filename, 4);
    if (file_extension == ".obj") {
        return mesh_file_parser_obj;
    } else if (file_extension == ".dae") {
        return mesh_file_parser_dae;
    }
}

string MeshFactory::lastCharacters(string input, int num) {
    return input.substr(input.size() - num);
}
