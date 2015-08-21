#ifndef Vertex_h
#define Vertex_h

struct MeshVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 binormal;
    glm::vec2 texcoord;

    bool operator==(const MeshVertex& rhs){
        return (position == rhs.position) && (normal == rhs.normal) &&
            (texcoord == rhs.texcoord);
    }
};

struct TerrainVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 binormal;
    glm::vec2 texcoord;
    glm::vec2 splatcoord;

};

#endif
