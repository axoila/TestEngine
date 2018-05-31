#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
	Mesh(std::vector<GLuint>* indices, std::vector<glm::vec3>* positions, std::vector<glm::vec2>* texCoords);
	~Mesh();

	static void FromObj(std::string filePath, std::vector<Mesh*>& output);

	void bindMesh();
	size_t getDrawCount() {
		return drawCount;
	}

	std::vector<glm::vec3>& GetPositions() {
		return positions;
	}

private:
	Mesh(Mesh& original);

	enum {
		POSITION_VB,
		TEXCOORD_VB,

		INDEX_VB,

		NUM_BUFFERS,
	};

	std::vector<GLuint> indices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffer[NUM_BUFFERS];

	size_t drawCount;
};
