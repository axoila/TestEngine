#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "Component.h"
#include "DirtyAble.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	glm::mat4 GetLocalModelMatrix();
	glm::mat4 GetWorldModelMatrix();

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::quat rotation);
	void SetScale(glm::vec3 scale);

	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();

	void LookAt(glm::vec3 target, glm::vec3 up = glm::vec3(0,1,0));

	void AddDirtyDependency(DirtyAble* newDependency);

	void RemoveDirtyDependency(DirtyAble* newDependency);

private:
	void Dirty();

	Transform* parent;

	bool localMatrixDirty = true;
	bool worldMatrixDirty = true;

	glm::mat4 worldModelMatrix;
	glm::mat4 localModelMatrix;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	std::vector<DirtyAble*> dirtyDependencies;
};

