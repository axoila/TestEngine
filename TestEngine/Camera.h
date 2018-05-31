#pragma once

#include "Component.h"
#include "Transform.h"
#include "DirtyAble.h"

class Camera : public Component, public DirtyAble
{
public:
	Camera();
	~Camera();

	void AddToEntity(Entity * entity) override;

	glm::mat4 GetViewProjectionMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void SetFov(float fov);
	void SetNearFarPlanes(float near, float far);
	void SetAspectRatio(float ratio);

	void DirtyView();
	void DirtyProjection();
	void Dirty() override;

private:
	Transform * transform;

	float fov = 70;
	float nearPlane = 0.1f;
	float farPlane = 1000;
	float aspect = 1;

	glm::mat4 viewProjectionMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	bool projectionDirty = true;
	bool viewDirty = true;
};

