#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include"VBOClass.h"
class VAO
{
public:
	unsigned int VAO_id;

	VAO();
	void Link(VBO* vertex_buffer, unsigned int layout, unsigned int layout_num_elements, unsigned int total_num_elements,unsigned int offset);
	void Bind();
	void Unbind();
	void Delete();

};

#endif // !VAO_CLASS_H
