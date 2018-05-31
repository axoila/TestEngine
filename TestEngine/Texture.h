#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);
	~Texture();

	void bind(unsigned int unit);

private:
	GLuint textureObject;
};

