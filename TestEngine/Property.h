#pragma once

#include <string>

class Property
{
public:
	virtual void bind() {};

protected:
	std::string name;
};

