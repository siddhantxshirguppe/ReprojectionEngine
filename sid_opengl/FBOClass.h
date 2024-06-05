#ifndef FBO_CLASS_H
#define FBO_CLASS_H

class VBO
{
public:
	unsigned int FBO_id;

	VBO(float* vertex_data, int data_size);
	void Bind();
	void Unbind();
	void Delete();

};

#endif // !FBO_CLASS_H
