#ifndef OBJ_MGR_H
#define OBJ_MGR_H

#include <unordered_map>
#include <string>
#include <memory> 

struct Vertex {
    float x, y, z;
    float r, g, b;
};

struct ObjData {
    std::string objectId;
    std::vector<Vertex> vertices;
    std::vector<int> indices;
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

