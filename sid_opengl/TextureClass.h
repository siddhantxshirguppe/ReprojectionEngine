#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include<string>
class TEXTURE
{
private:
	uint8_t* m_img_bytes;
	int m_img_width;
	int m_img_height;
	int m_img_channels;
	unsigned int texture_id;
public:
	

	TEXTURE(std::string img_path);
	static void setSlot(int slot_num);
	void Bind_and_Write();
	void Bind();
	void Unbind();
	void Delete();

};

#endif // !TEXTURE_CLASS_H