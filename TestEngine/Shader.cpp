#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(vertexShader), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(fragmentShader), GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(program, shaders[i]);
	}

	//bind first attribute in buffer to position
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "uv");

	//link shader and check link status
	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	//validate shader
	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
}

Shader::~Shader()
{
	for (int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		std::cerr << "Error: Shader creation failed" << std::endl;
		return 0;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringsLength[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringsLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed: ");

	return shader;
}

void Shader::bind() {
	if (this == nullptr || program == 0) {
		std::cerr << "Error: shader not initialized" << std::endl;
		return;
	}

	glUseProgram(program);
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
