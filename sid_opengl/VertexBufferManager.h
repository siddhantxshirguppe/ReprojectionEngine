#ifndef VB0_MGR_H
#define VB0_MGR_H

#include<vector>
#include "ObjManager.h"
#include "VBOClass.h"
#include "EBOClass.h"
#include "VAOClass.h"
#include "TextureClass.h"
#include "glm/glm.hpp"
static int slotCounter = 0;
class VertexBufferManager
{
private:
	std::vector<Vertex>* m_vertexBufferData;
	std::vector<int>* m_indexBufferData;
	VBO* m_vertexBuffer;
	EBO* m_indexBuffer;
	VAO* m_vaoBuffer;
	std::vector<float> m_reformattedVertexBufferData;
	Location mLoc;
	bool mHasTextures;
	TEXTURE* m_textBuffer;

public:
	VBO* getVertexBuffer();
	EBO* getIndexBuffer();
	VAO* getVAOBuffer();
	TEXTURE* getTextBuffer();
	int BuildVertexBuffer();
	VertexBufferManager(std::vector<Vertex>* const vertexbufferPtr, std::vector<int>* const indexBufferPtr, const Location& loc, const bool& hasTextures, const std::string& texture_path);
	virtual glm::mat4 getModelMatrix();
	bool hasTexture();
};
#endif // !VB0_MGR_H