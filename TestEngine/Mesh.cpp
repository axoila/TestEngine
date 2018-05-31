#include "Mesh.h"

#include "OBJ_Loader.h"

Mesh::Mesh(std::vector<glm::vec3>* positions, std::vector<glm::vec2>* texCoords) {
	drawCount = positions->size();;

	//generate vertex array
	glGenVertexArrays(1, &vertexArrayObject);

	this->positions = *positions;
	this->texCoords = *texCoords;

	for (int i = 0; i < positions->size();i++) {
		std::cout << this->positions[i].x << "|" << this->positions[i].y << "|" << this->positions[i].z << std::endl;
	}
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

		
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayObject);
}

std::vector<Mesh>& Mesh::FromObj(std::string filePath)
{
	objl::Loader load;
	std::vector<Mesh> meshes;
	if (load.LoadFile(filePath)) {

	}
	return meshes;
}

void Mesh::bindMesh() 
{
	glBindVertexArray(vertexArrayObject);
}