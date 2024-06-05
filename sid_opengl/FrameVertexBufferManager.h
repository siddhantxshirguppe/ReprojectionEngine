#ifndef FVB0_MGR_H
#define FVB0_MGR_H

#include"VertexBufferManager.h"
#include"CameraViewManager.h";

class FrameVertexBufferManager:public VertexBufferManager
{
private:
	CameraViewManager* camMgr;
public:
	FrameVertexBufferManager(std::vector<Vertex>* const vertexbufferPtr, std::vector<int>* const indexBufferPtr, const Location& loc, const bool& hasTextures, const std::string& texture_path,CameraViewManager* camMgr);
	glm::mat4 getModelMatrix() override;

};
#endif // !FVB0_MGR_H
