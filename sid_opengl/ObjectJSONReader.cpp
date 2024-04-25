#include "ObjectJSONReader.h"
#include "ObjManager.h"
using namespace rapidjson;
int ObjectJSONReader::readObjectData(const std::string& filename)
{
    

    // Read the JSON file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open JSON file." << std::endl;
        return -1;
    }

    // Parse the JSON document
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);

    if (doc.HasParseError()) {
        std::cerr << "JSON parse error: " << doc.GetParseError() << std::endl;
        return -1;
    }

    // Ensure the document contains an "Objects" array
    if (!doc.HasMember("Objects") || !doc["Objects"].IsArray()) {
        std::cerr << "JSON parse error: Missing or invalid 'Objects' array." << std::endl;
        return -1;
    }

    const Value& objectsArray = doc["Objects"];

    //get the obj store
    ObjManager* objMgr = ObjManager::getInstance();
    // Process each cube object
    for (SizeType i = 0; i < objectsArray.Size(); ++i)
    {
        const Value& object = objectsArray[i];

        // Get object ID
        const auto& objectName = object.MemberBegin()->name.GetString();
        std::cout << "pasrsing object:" << objectName << std::endl;

        // Get the object data
        const auto& objectData = object.MemberBegin()->value.GetObject();

        // Ensure each cube object contains "object_id", "position", and "color"
        if (!objectData.HasMember("position") || !objectData.HasMember("color") || !objectData.HasMember("index")) {
            std::cerr << "Cube object at index " << i << " does not contain  position, or color or index" << std::endl;
            continue;
        }

        


        // Get position and color arrays
        const Value& positions = objectData["position"];
        const Value& colors = objectData["color"];
        const Value& indices = objectData["index"];

        // Ensure position and color arrays have the same length
        if (!positions.IsArray() || !colors.IsArray() || !indices.IsArray() || positions.Size() != colors.Size()) {
            std::cerr << "Position and color arrays of cube " << objectName << " must be arrays of the same length." << std::endl;
            continue;
        }

        ObjData objData;

        // Process each vertex of the cube
        for (SizeType j = 0; j < positions.Size(); ++j) {
            const Value& pos = positions[j];
            const Value& col = colors[j];

            // Ensure each vertex has x, y, z coordinates
            if (!pos.IsArray() || pos.Size() != 3 || !col.IsArray() || col.Size() != 3) {
                std::cerr << "Invalid position or color format at vertex " << j << " of cube " << objectName << std::endl;
                continue;
            }

            // Extract position and color data
            Vertex vertex;
            vertex.x = pos[0].GetFloat();
            vertex.y = pos[1].GetFloat();
            vertex.z = pos[2].GetFloat();
            vertex.r = col[0].GetFloat();
            vertex.g = col[1].GetFloat();
            vertex.b = col[2].GetFloat();

            // Add vertex to cube data
            objData.vertices.push_back(vertex);

        }

        //add the index data
        for (SizeType j = 0; j < indices.Size(); ++j) {
            objData.indices.push_back(indices[j].GetInt());
        }




        objData.objectId = objectName;
        (*(objMgr->ObjectStore))[objData.objectId] = objData;

       


    }



    return 0;
}
