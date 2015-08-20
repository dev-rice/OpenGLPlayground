// mesh_loader.cpp
// implementation of the model class
// Trevor Westphal

#include "MeshFileParserOBJ.hpp"


MeshFileParserOBJ::MeshFileParserOBJ(string filename){
    loadMeshFromFile(filename);
}

std::vector<GLfloat> MeshFileParserOBJ::getVertexArray(){
    return final_vertices;
}

std::vector<GLuint> MeshFileParserOBJ::getFaceArray(){
    return final_faces;
}

void MeshFileParserOBJ::loadMeshFromFile(string filename){
    const char* fileName = filename.c_str();

    float tempX, tempY, tempZ;
    int tempA, tempB, tempC, tempD, tempE, tempF, tempG, tempH, tempI;

    std::vector<GLfloat> verts3D;
    std::vector<GLfloat> verts2D;
    std::vector<GLfloat> verts_norm;
    std::vector<GLuint> tris3D;
    std::vector<GLuint> tris2D;
    std::vector<GLuint> norms3D;

    int triCount = 0;

    char buffer[128];

    FILE *ifile;
    ifile = fopen(fileName, "r");

    if(ifile == NULL){
        printf("Error opening file %s\n", fileName);
        return;

    }

    while(! feof(ifile)){
        if(fgets(buffer, 128, ifile) == NULL){
            // Can't read into buffer
            break;
        }

        if(buffer[0] == 'v'){
            if(buffer[1] == 't'){
                // texture vertex
                sscanf(buffer, "%*2c %f %f", &tempX, &tempY);
                verts2D.push_back((GLfloat)tempX);
                verts2D.push_back((GLfloat)(1.0f - tempY));
            } else if (buffer[1] == 'n'){
                sscanf(buffer, "%*2c %f %f %f", &tempX, &tempY, &tempZ);
                verts_norm.push_back((GLfloat)tempX);
                verts_norm.push_back((GLfloat)tempY);
                verts_norm.push_back((GLfloat)tempZ);
            } else {
                // 3d vertex
                sscanf(buffer, "%*c %f %f %f", &tempX, &tempY, &tempZ);
                verts3D.push_back((GLfloat)tempX);
                verts3D.push_back((GLfloat)tempY);
                verts3D.push_back((GLfloat)tempZ);
            }
        } else if(buffer[0] == 'f'){
            // Face declarations
            sscanf(buffer, "%*c %d/%d/%d %d/%d/%d %d/%d/%d", &tempA, &tempD, &tempG, &tempB, &tempE, &tempH, &tempC, &tempF, &tempI);
            tris3D.push_back((GLuint)tempA);
            tris3D.push_back((GLuint)tempB);
            tris3D.push_back((GLuint)tempC);
            tris2D.push_back((GLuint)tempD);
            tris2D.push_back((GLuint)tempE);
            tris2D.push_back((GLuint)tempF);
            norms3D.push_back((GLuint)tempG);
            norms3D.push_back((GLuint)tempH);
            norms3D.push_back((GLuint)tempI);

            triCount++;
        }
    }

    fclose(ifile);

    // Setting up the data structure to see if vertex mapping has already been done
    int count = 1;

    std::map<std::array<GLuint, 2>, GLuint> mappedEdgeLoops;

    for(int i(0); i < triCount; ++i){

        for(int j(0); j < 3; ++j){

            std::array<GLuint, 2> tuple = {tris3D[i*3+j], tris2D[i*3+j]};

            int result = mappedEdgeLoops[tuple];

            if(result == 0){
                // Has not been declared yet
                mappedEdgeLoops[tuple] = count;
                count++;

                // Acessing 3D vertices indicated by the connection list
                tempX = verts3D[ (tuple[0]-1)*3+0 ];
                tempY = verts3D[ (tuple[0]-1)*3+1 ];
                tempZ = verts3D[ (tuple[0]-1)*3+2 ];

                // Acessing 3D normal vertices indicated by the connection list
                GLuint something = norms3D[i*3 + j];
                GLfloat tempVN1 = verts_norm[(something - 1)*3 +0 ];
                GLfloat tempVN2 = verts_norm[ (something - 1)*3 +1 ];
                GLfloat tempVN3 = verts_norm[(something - 1)*3 +2  ];

                // Acessing 2D vertices indicated by the connection list
                GLfloat tempX2 = verts2D[ (tuple[1]-1)*2+0 ];
                GLfloat tempY2 = verts2D[ (tuple[1]-1)*2+1 ];

                final_vertices.push_back(tempX);
                final_vertices.push_back(tempY);
                final_vertices.push_back(tempZ);
                final_vertices.push_back(tempVN1);
                final_vertices.push_back(tempVN2);
                final_vertices.push_back(tempVN3);
                final_vertices.push_back(tempX2);
                final_vertices.push_back(tempY2);
            }
            final_faces.push_back(mappedEdgeLoops[tuple]-1);
        }
    }

}
