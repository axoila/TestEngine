#pragma once

#include <vector>

#include "Property.h"
#include "Shader.h"

class Material
{
public:
	Material(Shader* shader);
	~Material();

	void bind();

	void addProperty(Property* newProperty) {
		properties.push_back(newProperty);
	}

	Shader* GetShader() {
		return shader;
	}

	void SetCull(int cullMode) {
		culling = cullMode;
	}
	void SetDepthTest(int depthMode) {
		depthTest = depthMode;
	}

	enum {
		NONE,
		BACK,
		FRONT,
	};

	enum {
		ALWAYS,
		GREATER,
		LESS,
		EQUAL
	};

private:
	int culling = NONE;
	int depthTest = NONE;

	Shader* shader;
	std::vector<Property*> properties;
};

