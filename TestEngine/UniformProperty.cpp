#include "UniformProperty.h"

void UniformProperty::bindUniform(GLuint program)
{
	uniformObject = glGetUniformLocation(program, name.c_str());
}
