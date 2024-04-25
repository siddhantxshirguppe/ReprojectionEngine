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
	cout << "hello world!" << endl;

	if (!glfwInit()) {
		cout << "Failed to initialize GLFW" << endl;
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
		cout << "failed to cerate window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(*window_ptr);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
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


	//write 
	//  vertex data 
	float model01_points[] = {
		//position		//colors		//text coords
		1.0f,  1.0f,	1.0,1.0,0.0f,	1.0f,1.0f,
		1.0f, -1.0f,	1.0,0.0,0.0f,	1.0f,0.0f,
	   -1.0f, -1.0f,	0.0,0.0,1.0f,	0.0f, 0.0f,
	   -1.0f,  1.0f,	0.0,1.0,1.0f,	0.0f,1.0f
	};

	unsigned int model01_indices[] =
	{
		0,
		1,
		2,
		0,
		2,
		3
	};
	//write the vertex data 
	float pyd_points[] = {

		//position			//colors		//text coords
		-0.5f, 0.0f, 0.5f,	1.0,1.0,0.0f,	0.0f,0.0f, //0
		-0.5f, 0.0f, -0.5f,	1.0,0.0,0.0f,	0.5f,0.0f, //1
		 0.5f, 0.0f, -0.5f,	0.0,0.0,1.0f,	0.0f,0.0f, //2
		 0.5f, 0.0f,0.5f,	0.0,1.0,1.0f,	0.5f,0.5f, //3
		0.0f, 0.8f, 0.0f,	0.0,1.0,1.0f,	0.25f,0.5f, //4

	};

	unsigned int pyd_indices[] = {

		0, 1, 2,  // Base triangle 1
		0, 2, 3,  // Base triangle 2
		0, 1, 4,  // Base triangle 3
		4, 3, 0,   // Side triangle 2
		1, 2, 4,  // Base triangle 4
		2, 3, 4,  // Side triangle 1

	};

	//create vertex and fragment objs and bundle them into a shader program and activate it



	unsigned int offset = 0;
	unsigned int stride = 8;

	//init textures for all the models

	//init texture_01
	TEXTURE texture_01("Resources/bridge.png");
	TEXTURE::setSlot(0); //activate slot 0 to write bridge image to slot 0
	texture_01.Bind_and_Write();

	cout << "debug checkpoint 01" << endl;
	//init vao for model 01
	VAO vao_01;
	VBO vbo_01(pyd_points, sizeof(pyd_points));
	EBO ebo_01(pyd_indices, sizeof(pyd_indices));
	offset = 0;
	vao_01.Link(vbo_01, 0, 3, stride, offset);
	offset = 3;
	vao_01.Link(vbo_01, 1, 3, stride, offset);
	offset = 6;
	vao_01.Link(vbo_01, 2, 2, stride, offset);

	cout << "debug checkpoint 02" << endl;

	Shader shader("Shaders/default00.vert", "Shaders/default00.frag");
	unsigned int scale_id = glGetUniformLocation(shader.getId(), "scale");
	unsigned int tex_slot_id = glGetUniformLocation(shader.getId(), "texture_slot");

	unsigned int modelLoc = glGetUniformLocation(shader.getId(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.getId(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.getId(), "proj");

	cout << "debug checkpoint 03" << endl;

	//deinit for texture_01
	texture_01.Unbind();

	//deinit for model 01
	vao_01.Unbind();
	vbo_01.Unbind();
	ebo_01.Unbind();


	//init a timer for rotation
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	//enable depth 
	glEnable(GL_DEPTH_TEST);

	cout << "debug checkpoint" << endl;


	int wnd_closed = glfwWindowShouldClose(window);

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Use the shader program
		shader.Activate();

		//initilize the mvp matrices 
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		//rotate the model matrix 
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation = rotation + 0.5f;
			prevTime = crntTime;
		}
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		//move the object arther away 
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);


		glUniform1f(scale_id, 0.5f);
		glUniform1i(tex_slot_id, 0);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		//toggle between vao_01 and vao_02
		vao_01.Bind();


		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			cout << "OpenGL Error: " << error << endl;
		}
		else
		{
			cout << "triangle drawn successfully!" << endl;
		}




		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao_01.Delete();
	ebo_01.Delete();
	vbo_01.Delete();


	texture_01.Delete();

	shader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}