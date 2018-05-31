#include "Mesh.h"

#include "OBJ_Loader.h"

Mesh::Mesh(
		std::vector<GLuint>* indices,
		std::vector<glm::vec3>* positions, 
		std::vector<glm::vec2>* texCoords) {

	drawCount = positions->size();

	//generate vertex array
	glGenVertexArrays(1, &vertexArrayObject);

	this->positions = *positions;
	this->texCoords = *texCoords;
	this->indices = *indices;

	std::cout << std::endl;

	//bind the vertex array
	glBindVertexArray(vertexArrayObject);
	//generate buffer for vertex data
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);
	//bind buffer for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
	//add data to GPU, 1: the type of data, 2: the size of the data, 3: the data, 4: hint how often the data will be changed
	glBufferData(GL_ARRAY_BUFFER, positions->size() *sizeof(this->positions[0]), &this->positions[0], GL_STATIC_DRAW);

	//which attribute are we setting up 1: index
	glEnableVertexAttribArray(0);
	//set up attribute 1:index 2:length (it's 3dimensional) 3:type 4:is it normalized 5: how far to jump after reading 6: where to start reading
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[TEXCOORD_VB]);
	//add data to GPU, 1: the type of data, 2: the size of the data, 3: the data, 4: hint how often the data will be changed
	glBufferData(GL_ARRAY_BUFFER, texCoords->size() * sizeof(this->texCoords[0]), &this->texCoords[0], GL_STATIC_DRAW);

	//which attribute are we setting up 1: index
	glEnableVertexAttribArray(1);
	//set up attribute 1:index 2:length (it's 3dimensional) 3:type 4:is it normalized 5: how far to jump after reading 6: where to start reading
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffer[INDEX_VB]);
	//add data to GPU, 1: the type of data, 2: the size of the data, 3: the data, 4: hint how often the data will be changed
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(this->indices[0]), &this->indices[0], GL_STATIC_DRAW);

		
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::FromObj(std::string filePath, std::vector<Mesh>* output)
{
	objl::Loader meshLoader;

	if (meshLoader.LoadFile(filePath)) {
		for (int i = 0; i < meshLoader.LoadedMeshes.size(); i++)
		{
			objl::Mesh currentMesh = meshLoader.LoadedMeshes[i];

			std::vector<GLuint>* indices = new std::vector<GLuint>;
			indices->reserve(currentMesh.Indices.size());

			indices = &std::vector<GLuint>(currentMesh.Indices);


			std::vector<glm::vec3>* positions = new std::vector<glm::vec3>;
			positions->reserve(currentMesh.Vertices.size());
			std::vector<glm::vec2>* texCoords = new std::vector<glm::vec2>;
			texCoords->reserve(currentMesh.Vertices.size());

			for (int j = 0; j < currentMesh.Vertices.size(); j++) {
				glm::vec3 pos(
						currentMesh.Vertices[j].Position.X, 
						currentMesh.Vertices[j].Position.Y, 
						currentMesh.Vertices[j].Position.Z);
				positions->push_back(pos);

				glm::vec2 uv(
						currentMesh.Vertices[j].TextureCoordinate.X, 
						currentMesh.Vertices[j].TextureCoordinate.Y);
				texCoords->push_back(uv);
			}


			output->emplace_back(indices, positions, texCoords);
		}
	}
}

void Mesh::bindMesh() 
{
	glBindVertexArray(vertexArrayObject);
}