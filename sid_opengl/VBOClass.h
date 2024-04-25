#ifndef VBO_CLASS_H
#define VBO_CLASS_H

class VBO
{
public:
	unsigned int VBO_id;

	VBO(float* vertex_data, int data_size);
	void Bind();
	void Unbind();
	void Delete();

};

#endif // !VBO_CLASS_H
