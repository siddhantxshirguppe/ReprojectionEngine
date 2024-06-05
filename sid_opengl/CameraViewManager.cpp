#include"CameraViewManager.h"

CameraViewManager* CameraViewManager::instance = nullptr;
CameraViewManager::CameraViewManager(GLFWwindow* win_ctx)
{
	KBMgr = KBControlManager::getInstance(win_ctx);
	MSMgr = MouseControlManager::getInstance(win_ctx);

	cameraPosition = glm::vec3(0.0f, 0.0f, -500.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
}

glm::mat4 CameraViewManager::getCameraView()
{

	if (KBMgr->moveForward)
	{
		// Move the camera towards the target by 1 unit
		glm::vec3 direction = glm::normalize(MSMgr->getLookDirection());  // Calculate direction towards the target

		cameraPosition += direction * moveAmount;  // Move the camera position by 1 unit towards the target

		// Regenerate the view matrix with the updated camera position
		view_mat = glm::lookAt(cameraPosition, cameraPosition + MSMgr->getLookDirection(), upVector);
	}
	else if (KBMgr->moveBackward)
	{
		// Move the camera towards the target by 1 unit
		glm::vec3 direction = glm::normalize(MSMgr->getLookDirection());  // Calculate direction towards the target
		cameraPosition -= direction * moveAmount;  // Move the camera position by 1 unit towards the target
		// Regenerate the view matrix with the updated camera position
		view_mat = glm::lookAt(cameraPosition, cameraPosition + MSMgr->getLookDirection(), upVector);
	}
	else if (KBMgr->moveRight)
	{
		// Compute the forward direction of the camera
		glm::vec3 forward = glm::normalize(MSMgr->getLookDirection());

		// Compute the right direction of the camera
		glm::vec3 right = glm::normalize(glm::cross(forward, upVector));

		cameraPosition += right * moveAmount;

		// Update the view matrix
		view_mat = glm::lookAt(cameraPosition, cameraPosition + MSMgr->getLookDirection(), upVector);
	}
	else if (KBMgr->moveLeft)
	{
		// Compute the forward direction of the camera
		glm::vec3 forward = glm::normalize(MSMgr->getLookDirection());

		// Compute the right direction of the camera
		glm::vec3 right = glm::normalize(glm::cross(forward, upVector));

		cameraPosition -= right * moveAmount;
		// Update the view matrix
		view_mat = glm::lookAt(cameraPosition, cameraPosition + MSMgr->getLookDirection(), upVector);
	}
	else
	{
		//handle mouse interactions
		view_mat = glm::lookAt(cameraPosition, cameraPosition+ MSMgr->getLookDirection(), upVector);
	}
	   

	return view_mat;
}

glm::vec3 CameraViewManager::getCameraPositon()
{
	return cameraPosition;
}

glm::vec3 CameraViewManager::getCameraDirection()
{
	return MSMgr->getLookDirection();
}

glm::vec3 CameraViewManager::getCameraUp()
{
	return upVector;
}
KBControlManager* CameraViewManager::getKBMgr()
{
	return KBMgr;
}
CameraViewManager* CameraViewManager::getInstance(GLFWwindow* window)
{
	if (!instance) {
		instance = new CameraViewManager(window); // Instantiate the singleton object using new operator
	}
	return instance;
}