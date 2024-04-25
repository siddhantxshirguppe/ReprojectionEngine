#include"VAOClass.h"
#include<glad/glad.h>
using namespace std;

VAO::VAO()
{
	glGenVertexArrays(1, &VAO_id);
	glBindVertexArray(VAO_id);
}

void VAO::Link(VBO& vertex_buffer, unsigned int layout,unsigned int layout_num_elements, unsigned int total_num_elements,unsigned int offset)
{
	vertex_buffer.Bind();

	glVertexAttribPointer(layout, layout_num_elements, GL_FLOAT, GL_FALSE, total_num_elements * sizeof(float), (void*)(offset*sizeof(float))); //slot 0 if for vertices
	glEnableVertexAttribArray(layout);

	vertex_buffer.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(VAO_id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &VAO_id);
}