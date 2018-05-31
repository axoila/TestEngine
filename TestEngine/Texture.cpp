#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string & fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL) {
		std::cerr << "Error: texture loading failed" << std::endl;
		return;
	}

	glGenTextures(1, &textureObject);
	glBindTexture(GL_TEXTURE_2D, textureObject);

	//make the texture wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureObject);
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureObject);
}
