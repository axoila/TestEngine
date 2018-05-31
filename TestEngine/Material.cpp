#include "Material.h"

#include <iostream>

Material::Material(Shader* shader)
{
	this->shader = shader;
}


Material::~Material()
{
	free(shader);
}

void Material::bind()
{
	//std::cout << "bind material" << std::endl;

	switch (culling) {
	case NONE:
		glDisable(GL_CULL_FACE);
		break;
	case BACK:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case FRONT:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	}

	switch (depthTest) {
	case ALWAYS:
		glDepthFunc(GL_ALWAYS);
		break;
	case LESS:
		glDepthFunc(GL_LESS);
		break;
	case GREATER:
		glDepthFunc(GL_GREATER);
		break;
	}

	shader->bind();
	for (Property* prop : properties) {
		prop->bind();
	}
}
