#include "MeshRenderer.h"

#include <iostream>

#include "RenderSystem.h"
#include "Mat4Property.h"

MeshRenderer::MeshRenderer(Mesh* renderMesh, Material* renderMaterial)
{
	mvpProperty = new Mat4Property("transform", glm::mat4(), renderMaterial->GetShader()->GetProgramObject());
	renderMaterial->addProperty(mvpProperty);

	this->renderMesh = renderMesh;
	this->renderMaterial = renderMaterial;

	RenderSystem::GetInstance()->AddRenderer(this);

	std::cout << "in renderer:" << this->renderMesh->GetPositions().size() << std::endl;
}


MeshRenderer::~MeshRenderer()
{
	RenderSystem::GetInstance()->RemoveRenderer(this);
}

void MeshRenderer::AddToEntity(Entity * entity)
{
	this->entity = entity;
	transform = entity->GetComponent<Transform>();
	if (transform == nullptr) {
		std::cerr << "meshrenderer can't find transform component, please add transform first!" << std::endl;
	}
}

void MeshRenderer::Draw() {

	renderMesh->bindMesh();
	renderMaterial->bind();
	
	if (transform == nullptr) {
		mvpProperty->SetValue(GetMvpMatrix());
	}
	else {
		mvpProperty->SetValue(GetMvpMatrix());
	}

	glDrawElements(GL_TRIANGLES, (GLsizei)renderMesh->getDrawCount(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, renderMesh->getDrawCount());

	glBindVertexArray(0);
}

glm::mat4 MeshRenderer::GetMvpMatrix()
{
	if (transform == nullptr) {
		return RenderSystem::GetInstance()->GetViewProjectionMatrix();
	}
	else {
		return RenderSystem::GetInstance()->GetViewProjectionMatrix() * transform->GetWorldModelMatrix();
	}
}
