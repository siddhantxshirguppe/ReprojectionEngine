#include"KBControlManager.h"
#include<iostream>

KBControlManager* KBControlManager::instance = nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    KBControlManager* kbManager = KBControlManager::getInstance(window);

    // Check if KBControlManager instance exists
    if (!kbManager) {
        std::cerr << "Failed to get KBControlManager instance" << std::endl;
        return;
    }

    // Update moveForward flag based on key press
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            kbManager->moveForward = true;
            std::cout << "W key pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            kbManager->moveForward = false;
            std::cout << "W key released" << std::endl;
        }
    }

    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            kbManager->moveBackward = true;
            std::cout << "S key pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            kbManager->moveBackward = false;
            std::cout << "S key released" << std::endl;
        }
    }

    if (key == GLFW_KEY_E) {
        if (action == GLFW_PRESS) {
            kbManager->turnRight = true;
            std::cout << "E key pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            kbManager->turnRight = false;
            std::cout << "E key released" << std::endl;
        }
    }

    if (key == GLFW_KEY_Q) {
        if (action == GLFW_PRESS) {
            kbManager->turnLeft= true;
            std::cout << "Q key pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            kbManager->turnLeft = false;
            std::cout << "Q key released" << std::endl;
        }
    }

    if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            kbManager->moveRight = true;
            std::cout << "D key pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            kbManager->moveRight = false;
            std::cout << "D key released" << std::endl;
        }
    }

    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            kbManager->moveLeft = true;
            std::cout << "A key pressed" << std::endl;
        }
        else if (action == GLFW_RELEASE) {
            kbManager->moveLeft = false;
            std::cout << "A key released" << std::endl;
        }
    }
}


KBControlManager::KBControlManager(GLFWwindow* window):turnLeft(false), turnRight(false), moveForward(false), moveBackward(false), m_windowPtr(nullptr)
{
    m_windowPtr = window;
	
}

KBControlManager* KBControlManager::getInstance(GLFWwindow* window)
{
	if (!instance) {
		instance = new KBControlManager(window); // Instantiate the singleton object using new operator
	}
	return instance;
}

int KBControlManager::registerCB()
{
    glfwSetKeyCallback(m_windowPtr, key_callback);
    return 0;
}