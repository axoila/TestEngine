#pragma once

#include "Property.h"
#include "Texture.h"
#include <string>

class TextureProperty : public Property
{
public:
	TextureProperty(const std::string& name, Texture* texture);
	~TextureProperty();

	void bind() override;

private:
	Texture* texture;

};

