#ifndef EBO_CLASS_H
#define EBO_CLASS_H

class EBO
{
public:
	unsigned int EBO_id;

	EBO(unsigned int* index_data, int num_elements);
	void Bind();
	void Unbind();
	void Delete();

};

#endif // !EBO_CLASS_H
