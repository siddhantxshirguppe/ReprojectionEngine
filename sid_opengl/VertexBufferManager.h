#ifndef VB0_MGR_H
#define VB0_MGR_H

#include<vector>
#include "ObjManager.h"
#include "VBOClass.h"
#include "EBOClass.h"
#include "VAOClass.h"
class VertexBufferManager
{
private:
	std::vector<Vertex>* m_vertexBufferData;
	std::vector<int>* m_indexBufferData;
	VBO* m_vertexBuffer;
	EBO* m_indexBuffer;
	VAO* m_vaoBuffer;
	std::vector<float> m_reformattedVertexBufferData;
public:
	VBO* getVertexBuffer();
	EBO* getIndexBuffer();
	VAO* getVAOBuffer();
	int BuildVertexBuffer();
	VertexBufferManager(std::vector<Vertex>* vertexbufferPtr, std::vector<int>* indexBufferPtr);
};

#endif // !VB0_MGR_H