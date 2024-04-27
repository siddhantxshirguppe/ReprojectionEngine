#include"EBOClass.h"
#include<glad/glad.h>
#include<iostream>

using namespace std;

EBO::EBO(int* index_data, int data_size)
{
	for (int i = 0;i < data_size/sizeof(int);i++)
	{
		std::cout << "index:" << index_data[i] << std::endl;
	}
	glGenBuffers(1, &EBO_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, index_data, GL_STATIC_DRAW); //ill it with the vertex data and bind(activate) it
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_id);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &EBO_id);
}