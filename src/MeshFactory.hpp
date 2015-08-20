#ifndef MeshFactory_h
#define MeshFactory_h

#include <string>

#include "Mesh.hpp"
#include "MeshFileParserDAE.hpp"
#include "MeshFileParserOBJ.hpp"

using namespace std;

class MeshFactory {
public:
    Mesh createMesh(string filename);

private:

    MeshFileParser& getCorrectParser(string filename);
    string lastCharacters(string input, int num);

    MeshFileParserOBJ mesh_file_parser_obj;
    MeshFileParserDAE mesh_file_parser_dae;

};

#endif
