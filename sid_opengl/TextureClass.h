#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include<string>
#include"glad/glad.h";

class TEXTURE
{
private:
	uint8_t* m_img_bytes;
	int m_img_width;
	int m_img_height;
	int m_img_channels;
	GLuint m_texture_id;
	int m_texture_slot;
public:
	

	TEXTURE(std::string img_path);
	void setSlot(int slot_num);
	void Bind_and_Write();
	void Bind();
	void Unbind();
	void Delete();
	void disableSlot();

};

#endif // !TEXTURE_CLASS_H