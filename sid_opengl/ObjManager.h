#ifndef OBJ_MGR_H
#define OBJ_MGR_H

#include <unordered_map>
#include <string>
#include <memory> 

struct Vertex {
    float x, y, z;
    float r, g, b;
    float s, t;

    Vertex() : x(0.0f), y(0.0f), z(0.0f), r(0.0f), g(0.0f), b(0.0f), s(0.0f), t(0.0f) {}

};

struct Vertex3D {
    float x, y, z;


    Vertex3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Vertex3D(float x, float y, float z) : x(x), y(y), z(z) {}

};
struct Vertex2D {
    float x, y;


    Vertex2D() : x(0.0f), y(0.0f) {}
    Vertex2D(float x, float y) : x(x), y(y) {}

};

struct Location {
    float x, y, z;
    float u, v, w;

    Location() : x(0.0f), y(0.0f), z(0.0f), u(0.0f), v(0.0f), w(0.0f) {}
};
struct ObjData {
    std::string objectId;
    std::string texturePath;
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    Location loc;
    bool hasTextures;

    ObjData() : objectId("000"), texturePath("000"), hasTextures(false) {
        // Initialize other members if needed
    }
};

class ObjManager
{
    public:
        ObjManager();
        std::unordered_map<std::string, ObjData>* ObjectStore;
        static ObjManager* instance;
        static ObjManager* getInstance();
};

#endif // !OBJ_MGR_H

