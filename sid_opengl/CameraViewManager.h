#ifndef CAMVIEW_MGR__H
#define CAMVIEW_MGR__H

#include"KBControlManager.h"
#include"MouseControlManager.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
class CameraViewManager
{
	private:
		KBControlManager* KBMgr;
		MouseControlManager* MSMgr;
		float moveAmount = 1.0f;
		float rotAmount = 1.0f;

		//view matrix 
		glm::vec3 cameraPosition;  // Camera position in world space
		glm::vec3 cameraTarget;    // Point the camera is looking at
		glm::vec3 upVector;
		glm::mat4 view_mat;

	public:
		CameraViewManager(GLFWwindow* win_ctx);
		static CameraViewManager* instance;
		static CameraViewManager* getInstance(GLFWwindow* window);

		glm::mat4 getCameraView();
		glm::vec3 getCameraPositon();
		glm::vec3 getCameraDirection();
		glm::vec3 getCameraUp();
		KBControlManager* getKBMgr();
};

#endif // !CAMVIEW_MGR__H