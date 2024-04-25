#include"shaderClass.h"
#include<glad/glad.h>
using namespace std;
// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
unsigned int Shader::getId()
{
	return shader_pgm_id;
}
unsigned int Shader::compile_myShader(unsigned int type, const string& shaderString)
{
	unsigned int shader_id = glCreateShader(type);
	const char* shader_src = shaderString.c_str();
	glShaderSource(shader_id, 1, &shader_src, NULL);
	glCompileShader(shader_id);

	//get the compile result of the shader_id 
	int res;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == 0)
	{
		if (type == GL_VERTEX_SHADER)
		{
			cout << "failed to compile VERTEX shader!!" << endl;
		}
		else if (type == GL_FRAGMENT_SHADER)
		{
			cout << "failed to compile FRAGMENT shader!!" << endl;
		}

		// Print compilation log
		char infoLog[512];
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		cout << "Shader Compilation Log for type " << type << ":\n" << infoLog << endl;
	}
	else
	{
		cout << "Shader compilation successful for type " << type << "!" << endl;
	}

	return shader_id;
}
Shader::Shader(const char* vert_file_ptr, const char* frag_file_ptr)
{
	string vert_str = get_file_contents(vert_file_ptr);
	string frag_str = get_file_contents(frag_file_ptr);

	const char* vertex_shader = vert_str.c_str();
	const char* fragment_shader = frag_str.c_str();

	shader_pgm_id = glCreateProgram();
	unsigned int vs_id = compile_myShader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs_id = compile_myShader(GL_FRAGMENT_SHADER, fragment_shader);

	glAttachShader(shader_pgm_id, vs_id);
	glAttachShader(shader_pgm_id, fs_id);

	glLinkProgram(shader_pgm_id);
	// Check for linking errors
	int linkStatus;
	glGetProgramiv(shader_pgm_id, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		cout << "Program failed to link!" << endl;

		// Print linking log
		char infoLog[512];
		glGetProgramInfoLog(shader_pgm_id, 512, NULL, infoLog);
		cout << "Program Linking Log:\n" << infoLog << endl;
	}
	else
	{
		cout << "Program Linking successful!"<< endl;
	}

	glValidateProgram(shader_pgm_id);

	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
}

void Shader::Activate()
{
	glUseProgram(shader_pgm_id);
}

void Shader::Delete()
{
	
}