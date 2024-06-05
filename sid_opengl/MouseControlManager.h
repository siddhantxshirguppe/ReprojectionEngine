#include<GLFW/glfw3.h>
#include "glm/glm.hpp"

class MouseControlManager
{
public:
	MouseControlManager(GLFWwindow* window);

	GLFWwindow* m_windowPtr;
	static MouseControlManager* instance;
	static MouseControlManager* getInstance(GLFWwindow* window);

	int registerCB();
	void setLookDirection(glm::vec3 dir);
	glm::vec3 getLookDirection();
	glm::vec3 mLookDirection;
	bool moveForward;
	bool moveBackward;
	bool moveRight;
	bool moveLeft;
};