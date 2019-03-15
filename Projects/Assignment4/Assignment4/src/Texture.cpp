#include <cassert>
#include <iostream>
#include "Texture.h"
#include "SOIL2\stb_image.h"

Texture::Texture(const char *filePathOfImage)
{
	// Tell OpenGL to create a texture buffer/object
	glGenTextures(1, &this->textureID);

	// Create variables to store information about the image 
	int width, height, numberOfComponents;
	// Read in the image with stbi image loader
	unsigned char *data = stbi_load(filePathOfImage, &width, &height, &numberOfComponents, 0);
	// Check if the data pointer is not null
	if (data)
	{
		// Determine the image's RGB format from the number of components determined from stbi loader
		GLenum format;
		if (numberOfComponents == 1)
			format = GL_RED;
		else if (numberOfComponents == 2)
			format = GL_RG;
		else if (numberOfComponents == 3)
			format = GL_RGB;
		else if (numberOfComponents == 4)
			format = GL_RGBA;

		// Bind the texture
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		// Place the image data into the texture buffer/object
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// Create mipmap for the texture
		glGenerateMipmap(GL_TEXTURE_2D);

		//Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		// Indicate to the user that the texture could not be loaded
		std::cerr << "Failed to load: " << filePathOfImage << std::endl;
	}

	stbi_image_free(data);
}

void Texture::UnbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindTexture(uint8_t textureUnit)
{
	assert(textureUnit >= 0 && textureUnit <= 31);

	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

GLuint Texture::GetTextureId()
{
	return this->textureID;
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->textureID);
}
