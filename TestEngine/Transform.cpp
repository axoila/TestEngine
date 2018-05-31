#include "Transform.h"

#include <iostream>

Transform::Transform()
{
	position = glm::vec3();
	rotation = glm::quat();
	scale = glm::vec3(1);
}


Transform::~Transform()
{
}

glm::mat4 Transform::GetLocalModelMatrix(){
	if (localMatrixDirty) {
		glm::mat4 posMatrix = glm::translate(position);
		glm::mat4 rotMatrix = glm::toMat4(rotation);
		glm::mat4 scaleMatrix = glm::scale(scale);

		localModelMatrix = posMatrix * rotMatrix * scaleMatrix;

		localMatrixDirty = false;
	}

	return localModelMatrix;
}

glm::mat4 Transform::GetWorldModelMatrix()
{
	if (worldMatrixDirty) {
		if (parent == nullptr) {
			worldModelMatrix = GetLocalModelMatrix();
		}
		else {
			worldModelMatrix = GetLocalModelMatrix() * parent->GetWorldModelMatrix();
		}

		worldMatrixDirty = false;
	}

	return worldModelMatrix;
}

void Transform::SetPosition(glm::vec3 position)
{
	this->position = position;
	Dirty();
}

void Transform::SetRotation(glm::quat rotation)
{
	this->rotation = rotation;
	Dirty();
}

void Transform::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	Dirty();
}

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::quat Transform::GetRotation()
{
	return rotation;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}

void Transform::LookAt(glm::vec3 target, glm::vec3 up)
{
	bool worldDirty = worldMatrixDirty;
	localModelMatrix = glm::lookAt(position, target, up) * glm::scale(scale);
	rotation = glm::toQuat(localModelMatrix);
	Dirty();
	//clean stuff up because we just rebuilt the whole matrix
	localMatrixDirty = false;
	worldMatrixDirty = worldDirty;
}

void Transform::AddDirtyDependency(DirtyAble * newDependency)
{
	dirtyDependencies.push_back(newDependency);
}

void Transform::RemoveDirtyDependency(DirtyAble * newDependency)
{
		for (auto it = dirtyDependencies.begin(); it != dirtyDependencies.end(); ) {
			if (*it == newDependency) {
				it = dirtyDependencies.erase(it);
			}
			else {
				++it;
			}
		}
}

void Transform::Dirty() {
	localMatrixDirty = true;
	worldMatrixDirty = true;

	//TODO dirty children

	for (DirtyAble* dependant : dirtyDependencies) {
		dependant->Dirty();
	}
}

