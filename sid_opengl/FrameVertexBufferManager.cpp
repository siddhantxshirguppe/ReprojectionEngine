#include "FrameVertexBufferManager.h"

glm::mat4 lookAtTarget(glm::vec3 objectPosition, glm::vec3 targetPosition, glm::vec3 upVector) {
	glm::vec3 direction = glm::normalize(targetPosition - objectPosition);
	return glm::lookAt(objectPosition, objectPosition + direction, upVector);
}

glm::mat4 FrameVertexBufferManager::getModelMatrix()
{

	bool frameStop = camMgr->getKBMgr()->frameStop;

	static glm::vec3 lastQuadPosition;
	static glm::vec3 lastCamPosition;

	if (!frameStop)
	{
		glm::vec3 cameraPos = camMgr->getCameraPositon();
		glm::vec3 cameraDir = camMgr->getCameraDirection();
		glm::vec3 quadPosition = cameraPos + cameraDir * 100.0f; // Adjust based on current camera position and orientation

		lastQuadPosition = quadPosition;
		lastCamPosition = cameraPos;
		glm::mat4 modelMatrix = glm::inverse(lookAtTarget(quadPosition, cameraPos, glm::vec3(0, 1, 0)));
		return modelMatrix;
	}
	else
	{
		glm::mat4 modelMatrix = glm::inverse(lookAtTarget(lastQuadPosition, lastCamPosition, glm::vec3(0, 1, 0)));
		return modelMatrix;
	}

}

FrameVertexBufferManager::FrameVertexBufferManager(std::vector<Vertex>* const vertexbufferPtr, std::vector<int>* const indexBufferPtr, const Location& loc, const bool& hasTextures, const std::string& texture_path, CameraViewManager* camManager):VertexBufferManager(vertexbufferPtr, indexBufferPtr, loc, hasTextures, texture_path)
{
	camMgr = camManager;
}