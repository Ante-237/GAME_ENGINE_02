#include "LightRenderer.h"


LightRenderer::LightRenderer(MeshType meshType, Camera* camera) {

	this->camera = camera;

	switch (meshType) {
	case kTriangle:
		Mesh::setTriData(vertices, indices);
		break;
	case kQuad:
		Mesh::setQuadData(vertices, indices);
		break;
	case kCube:
		Mesh::setCubeData(vertices, indices);
		break;
	case kSphere:
		Mesh::setSphereData(vertices, indices);
		break;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::color)));


	// creating element buffer

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void LightRenderer::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0), position);
	glUseProgram(this->program);

	GLint modelLoc = glGetUniformLocation(program, "model");
}