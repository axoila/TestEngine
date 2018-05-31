#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>


#include "OBJ_Loader.h"

class Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& uv) {
		this->pos = pos;
		this->uv = uv;
	}

	inline glm::vec3& getPos() {
		return pos;
	}
	inline glm::vec2& getUv() {
		return uv;
	}
private:
	glm::vec3 pos;
	glm::vec2 uv;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();

	static std::vector<Mesh>& FromObj(std::string filePath) {
		objl::Loader load;
		std::vector<Mesh> meshes;
		if (load.LoadFile(filePath)) {

		}
		return meshes;
	}

	void bindMesh();
	GLuint getDrawCount() {
		return drawCount;
	}

private:
	enum {
		POSITION_VB,
		TEXCOORD_VB,

		NUM_BUFFERS
	};

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];

	unsigned int drawCount;
};
