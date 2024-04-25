#ifndef OBJ_JSON_READER_CLASS_H
#define OBJ_JSON_READER_CLASS_H

#include <iostream>
#include <fstream>
#include <vector>

#include"ObjManager.h"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"




class ObjectJSONReader
{
public:
	static int readObjectData(const std::string& filename);

};

#endif 
