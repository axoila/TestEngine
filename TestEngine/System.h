#pragma once
class System
{
public:

	virtual void Update() {};

	virtual void Init() {};
	virtual void Clean() {};

	virtual bool Running() { return false; };
};

