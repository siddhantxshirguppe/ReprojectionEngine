#include<GLFW/glfw3.h>

class KBControlManager
{
	public:
		KBControlManager(GLFWwindow* window);

		GLFWwindow* m_windowPtr;
		static KBControlManager* instance;
		static KBControlManager* getInstance(GLFWwindow* window);

		int registerCB();
		bool turnLeft;
		bool turnRight;
		bool moveForward;
		bool moveBackward;
		bool moveRight;
		bool moveLeft;
};
