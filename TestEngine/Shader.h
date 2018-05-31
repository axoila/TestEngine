#pragma once

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	void bind();
	GLuint GetProgramObject() {
		return program;
	}

private:
	//make shader amount expandable for geometry and tesselation in the future maybe
	static const unsigned int NUM_SHADERS = 2;

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	GLuint program;
	GLuint shaders[NUM_SHADERS];
};

