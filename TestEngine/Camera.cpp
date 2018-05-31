#include "Camera.h"

#include <iostream>

#include "Entity.h"
#include "RenderSystem.h"

typedef void(*staticCameraFunction)(Camera*);

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::AddToEntity(Entity * entity)
{
	this->entity = entity;
	transform = entity->GetComponent<Transform>();
	if (transform == nullptr) {
		std::cerr << "camera can't find transform component, please add transform first!" << std::endl;
		return;
	}
	transform->AddDirtyDependency(this);
	RenderSystem::GetInstance()->SetActiveCamera(this, true);
}

glm::mat4 Camera::GetViewProjectionMatrix()
{
	if (projectionDirty || viewDirty) {
		viewProjectionMatrix = GetProjectionMatrix() * GetViewMatrix();
	}

	return viewProjectionMatrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	if (viewDirty) {
		viewMatrix = transform->GetWorldModelMatrix();
		viewDirty = false;
	}
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	if (projectionDirty) {
		projectionMatrix = glm::perspective(fov, aspect, nearPlane, farPlane);
		projectionDirty = false;
	}
	return projectionMatrix;
}

void Camera::SetFov(float fov)
{
	this->fov = fov;
	projectionDirty = true;
}

void Camera::SetNearFarPlanes(float near , float far)
{
	nearPlane = near;
	farPlane = far;
	projectionDirty = true;
}

void Camera::SetAspectRatio(float ratio)
{
	aspect = ratio;
	projectionDirty = true;
}

void Camera::DirtyView()
{
	viewDirty = true;
}

void Camera::DirtyProjection()
{
	projectionDirty = true;
}

void Camera::Dirty()
{
	DirtyView();
}