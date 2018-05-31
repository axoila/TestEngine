#pragma once

#include <string>
#include <glm/glm.hpp>

#include "UniformProperty.h"

class Mat4Property : public UniformProperty
{
public:
	Mat4Property(const std::string& name, glm::mat4 value);
	Mat4Property(const std::string& name, glm::mat4 value, GLuint program);
	~Mat4Property();

	void SetValue(glm::mat4 value);
private:
	glm::mat4 value;
};

