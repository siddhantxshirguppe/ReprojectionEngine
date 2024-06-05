#include"MouseControlManager.h"
#include<iostream>

MouseControlManager* MouseControlManager::instance = nullptr;

bool firstMouse = true;
float lastX = 0.0;
float lastY = 0.0;

float yaw = 0.0f;
float pitch = 0.0f;
float sensitivity = 0.1;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    

    float xOffset = 0.0;
    float yOffset = 0.0;

    if (firstMouse)
    {
        firstMouse = false;
        xOffset = 0.0;
        yOffset = 0.0;

        lastX = xpos;
        lastY = ypos;

    }
    else
    {
        xOffset = xpos - lastX;
        yOffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

    }

    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;

    //std::cout << "Mouse position: (yaw: " << yaw << ", pitch: " << pitch << ")" << std::endl;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 normalizedFront = glm::normalize(front);

    MouseControlManager* manager = MouseControlManager::getInstance(window);
    if (manager) {
        manager->setLookDirection(normalizedFront);
    }


}

MouseControlManager::MouseControlManager(GLFWwindow* window) :mLookDirection(0,0,0), moveForward(false), moveBackward(false), m_windowPtr(nullptr)
{
    m_windowPtr = window;

}

MouseControlManager* MouseControlManager::getInstance(GLFWwindow* window)
{
    if (!instance) {
        instance = new MouseControlManager(window); // Instantiate the singleton object using new operator
    }
    return instance;
}

int MouseControlManager::registerCB()
{
    glfwSetCursorPosCallback(m_windowPtr, mouse_callback);
    glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    return 0;
}

void MouseControlManager::setLookDirection(glm::vec3 dir)
{
    mLookDirection = dir;
    std::cout << "mLookDirection: (x: " << mLookDirection.x << ", y: " << mLookDirection.x << ", z: " << mLookDirection.z<< ")" << std::endl;
}

glm::vec3 MouseControlManager::getLookDirection()
{
    return mLookDirection;
}