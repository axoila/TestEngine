#include "TextureProperty.h"

TextureProperty::TextureProperty(const std::string& name, Texture* texture) {
	this->name = name;
	this->texture = texture;
}


TextureProperty::~TextureProperty()
{
}

void TextureProperty::bind()
{
	texture->bind(0);
}
