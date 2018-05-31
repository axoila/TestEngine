#pragma once

#include <GL/glew.h>

#include "Property.h"

class UniformProperty : public Property 
{
public:
	void bindUniform(GLuint program);

protected:
	GLuint uniformObject;
};