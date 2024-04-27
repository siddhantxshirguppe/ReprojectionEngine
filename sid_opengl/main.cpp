#include<iostream>
#include <windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"TextureClass.h"
#include "STB/stb_image.h"
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include"ObjectJSONReader.h"
#include"ShaderClass.h"
#include"VAOClass.h"
#include"VBOClass.h"
#include"EBOClass.h"
#include"ObjManager.h"
#include "VertexBufferManager.h"
#include "KBControlManager.h"


using namespace std;
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}


int init_engine(GLFWwindow** window_ptr)
{
	std::cout << "hello world!" << endl;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << endl;
		return -1;
	}


	//tell which opengl version to use while creating window 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	*window_ptr = glfwCreateWindow(800, 800, "test_window_title", NULL, NULL);
	if (*window_ptr == NULL)
	{
		std::cout << "failed to cerate window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(*window_ptr);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << endl;
		glfwTerminate();
		return -1;
	}

	int ctx_flags = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &ctx_flags);

	if (ctx_flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}


	glfwMakeContextCurrent(*window_ptr);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	KBControlManager* KBMgr = KBControlManager::getInstance(*window_ptr);
	KBMgr->registerCB();

	const GLubyte* glVersion = glGetString(GL_VERSION);
	if (glVersion) {
		std::cout << "OpenGL Version: " << glVersion << std::endl;
	}
	else {
		std::cerr << "Failed to get OpenGL version" << std::endl;
	}

	return 0;
}

int main()
{
	GLFWwindow* window = nullptr;
	assert(init_engine(&window) == 0);

	assert(ObjectJSONReader::readObjectData("Objects.json") == 0);
	

	ObjManager* objmgr = ObjManager::getInstance();
	// Access the ObjectStore dictionary
	auto& objectStore = *(objmgr->ObjectStore);

	// Iterate through the dictionary and print values
	for (const auto& pair : objectStore) {
		const auto& objectId = pair.first;
		const auto& objData = pair.second;

		std::cout << "Object ID: " << objectId << std::endl;
		std::cout << "Vertices:" << std::endl;
		for (const auto& vertex : objData.vertices) {
			std::cout << "  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;
		}
		std::cout << std::endl;
		for (const auto& index : objData.indices) {
			std::cout << "  (" << index << ")" << std::endl;
		}
	}


	Shader shader("Shaders/default00.vert", "Shaders/default00.frag");
	VertexBufferManager* ground_obj = new VertexBufferManager(&objectStore["Ground"].vertices, &objectStore["Ground"].indices);
	VertexBufferManager* cube02_obj = new VertexBufferManager(&objectStore["Cube02"].vertices, &objectStore["Cube02"].indices);

	
	//enable depth 
	glEnable(GL_DEPTH_TEST);



	int wnd_closed = glfwWindowShouldClose(window);
	// Use the shader program
	shader.Activate();

	//view matrix 
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -500.0f);  // Camera position in world space
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 1.0f);    // Point the camera is looking at
	glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);

	//init a timer for rotation
	float rotation = 0.0f;
	float translation = 0.0f;
	double prevTime = glfwGetTime();

	unsigned int projLoc = glGetUniformLocation(shader.getId(), "proj");
	unsigned int modelLoc = glGetUniformLocation(shader.getId(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.getId(), "view");
	glm::mat4 proj = glm::perspective(glm::radians(30.0f), (float)(800 / 800), 50.0f, 500.0f);
	//glm::mat4 proj = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f,0.1f,1000.0f);
	 //glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glm::mat4 model = glm::mat4(1.0f);

	//setup KB controls

	KBControlManager* KBMgr = KBControlManager::getInstance(window);


	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

		//MODIFY the model matrix 

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation = rotation + 0.5f;
			prevTime = crntTime;
			translation = translation + 0.001f;
			//std::cout << "rotation:" << rotation << std::endl;
			//std::cout << "translation:" << rotation << std::endl;
		}
		
		 glm::mat4 model_mat = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));


		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_mat));


		 //MODIFY the camera view matrix
		 float moveAmount = 4.0f;
		 float rotAmount = 1.0f;
		 if (KBMgr->moveForward)
		 {
			 // Move the camera towards the target by 1 unit
			 glm::vec3 direction = glm::normalize(cameraTarget - cameraPosition);  // Calculate direction towards the target
			 
			 cameraPosition += direction* moveAmount;  // Move the camera position by 1 unit towards the target

			 // Regenerate the view matrix with the updated camera position
			 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
		 }
		 else if (KBMgr->moveBackward)
		 {
			 // Move the camera towards the target by 1 unit
			 glm::vec3 direction = glm::normalize(cameraTarget - cameraPosition);  // Calculate direction towards the target
			 cameraPosition -= direction* moveAmount;  // Move the camera position by 1 unit towards the target

			 // Regenerate the view matrix with the updated camera position
			 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
		 }
		 else if (KBMgr->moveRight)
		 {
			 // Compute the forward direction of the camera
			 glm::vec3 forward = glm::normalize(cameraTarget - cameraPosition);

			 // Compute the right direction of the camera
			 glm::vec3 right = glm::normalize(glm::cross(forward, upVector));

			 cameraPosition += right * moveAmount;
			 cameraTarget += right * moveAmount;

			 // Update the view matrix
			 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
		 }
		 else if (KBMgr->moveLeft)
		 {
			 // Compute the forward direction of the camera
			 glm::vec3 forward = glm::normalize(cameraTarget - cameraPosition);

			 // Compute the right direction of the camera
			 glm::vec3 right = glm::normalize(glm::cross(forward, upVector));

			 cameraPosition -= right * moveAmount;
			 cameraTarget -= right * moveAmount;
			 // Update the view matrix
			 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
		 }
		 else if (KBMgr->turnRight)
		 {
			 glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-1* rotAmount), glm::vec3(0.0f, 1.0f, 0.0f));

			 glm::vec4 rotatedTarget = rotation * glm::vec4(cameraTarget - cameraPosition, 1.0f);

			 cameraTarget = glm::vec3(rotatedTarget) + cameraPosition;

			 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
		 }

		 else if (KBMgr->turnLeft)
		 {
			 glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rotAmount), glm::vec3(0.0f, 1.0f, 0.0f));

			 glm::vec4 rotatedTarget = rotation * glm::vec4(cameraTarget - cameraPosition, 1.0f);

			 cameraTarget = glm::vec3(rotatedTarget) + cameraPosition;

			 view_mat = glm::lookAt(cameraPosition, cameraTarget, upVector);
		 }



		 std::cout << "cameraPosition x: " << cameraPosition.x << ", y: " << cameraPosition.y << ", z: " << cameraPosition.z << std::endl;

		 glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_mat));
		 cube02_obj->getVAOBuffer()->Bind();
		 glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		 //toggle between vao_01 and vao_02
		 ground_obj->getVAOBuffer()->Bind();
		 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		 glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);

		//object_02->getVAOBuffer()->Bind();

		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << error << endl;
		}
		else
		{
			//std::cout << "triangle drawn successfully!" << endl;
		}

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	return 0;
}