#include"TextureClass.h"
#include"STB/stb_image.h"
#include<glad/glad.h>
#include<iostream>
using namespace std;
TEXTURE::TEXTURE(std::string image_path)
{
	//create and bind the texture buffer
	glGenTextures(1, &texture_id);
	glBindTexture(GL_PROXY_TEXTURE_2D, texture_id);

	//load the image

	stbi_set_flip_vertically_on_load(true);
	const char* img_path_cstr = image_path.c_str();
	m_img_bytes = stbi_load(img_path_cstr, &m_img_width, &m_img_height, &m_img_channels,0);
	cout << "img height:" << m_img_height << "width:" << m_img_width << "channels:" << m_img_channels << endl;
}

void TEXTURE::setSlot(int slot_num)
{
	glActiveTexture(GL_TEXTURE0 + slot_num);
}

void TEXTURE::Bind_and_Write()
{
	glBindTexture(GL_PROXY_TEXTURE_2D, texture_id);

	//4 required calls 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //gives a pixelated style 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //gives a pixelated style 


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //gives repeated texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //gives repeated texture

	//write the image data to buffer 
	if (m_img_channels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_img_width, m_img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_img_bytes);
	}
	else if (m_img_channels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_img_width, m_img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_img_bytes);
	}
	
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(m_img_bytes);
	//unbind for safety 
	glBindTexture(GL_PROXY_TEXTURE_2D, 0);
}

void TEXTURE :: Bind()
{
	glBindTexture(GL_PROXY_TEXTURE_2D, texture_id);
}
void TEXTURE::Unbind()
{
	glBindTexture(GL_PROXY_TEXTURE_2D, 0);
}

void TEXTURE::Delete()
{
	glDeleteTextures(1, &texture_id);
}