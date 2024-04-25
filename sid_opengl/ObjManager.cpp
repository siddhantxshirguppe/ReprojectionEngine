#include"ObjManager.h"

ObjManager* ObjManager::instance = nullptr;

ObjManager* ObjManager::getInstance()
{
    if (!instance) {
        instance = new ObjManager(); // Instantiate the singleton object using new operator
    }
    return instance;
}


ObjManager::ObjManager()
{
	ObjectStore = new std::unordered_map<std::string, ObjData>();
}

