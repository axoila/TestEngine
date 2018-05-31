#include "Mat4Property.h"


Mat4Property::Mat4Property(const std::string & name, glm::mat4 value)
{
	this->name = name;
	this->value = value;
}

Mat4Property::Mat4Property(const std::string & name, glm::mat4 value, GLuint program)
{
	this->name = name;
	bindUniform(program);

}

Mat4Property::~Mat4Property()
{
}

void Mat4Property::SetValue(glm::mat4 value)
{
	this->value = value;
	glUniformMatrix4fv(uniformObject, 1, GL_FALSE, &value[0][0]);
}
