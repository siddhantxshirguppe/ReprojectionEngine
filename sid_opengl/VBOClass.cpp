#include"VBOClass.h"
#include<glad/glad.h>
#include<iostream>

using namespace std;

VBO::VBO(float* vertex_data,int data_size)
{
	for (int i = 0;i < data_size/sizeof(float);i++)
	{
		std::cout << "vertex:" << vertex_data[i] << std::endl;
	}

	glGenBuffers(1, &VBO_id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
	glBufferData(GL_ARRAY_BUFFER, data_size, vertex_data, GL_STATIC_DRAW); //ill it with the vertex data and bind(activate) it
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &VBO_id);
}