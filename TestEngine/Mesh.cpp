#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices) {
	drawCount = numVertices;

	//generate vertex array
	glGenVertexArrays(1, &vertexArrayObject);

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++) {
		positions.push_back(vertices[i].getPos());
		texCoords.push_back(vertices[i].getUv());
	}

	//bind the vertex array
	glBindVertexArray(vertexArrayObject);
	//generate buffer for vertex data
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffer);
	//bind buffer for vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[POSITION_VB]);
	//add data to GPU, 1: the type of data, 2: the size of the data, 3: the data, 4: hint how often the data will be changed
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	//which attribute are we setting up 1: index
	glEnableVertexAttribArray(0);
	//set up attribute 1:index 2:length (it's 3dimensional) 3:type 4:is it normalized 5: how far to jump after reading 6: where to start reading
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer[TEXCOORD_VB]);
	//add data to GPU, 1: the type of data, 2: the size of the data, 3: the data, 4: hint how often the data will be changed
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

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

void Mesh::bindMesh() 
{
	glBindVertexArray(vertexArrayObject);
}