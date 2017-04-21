#include "Line.h"

Line::Line() {
	transformation = glm::mat4(1.0f);
	float coords[] = { 0, 0, 0, 0, 0, 5 };

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, 6, &coords[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), (GLvoid*)0);

	glBindVertexArray(0);
}

void Line::Draw(GLuint shader) {
	glUniform3f(glGetUniformLocation(shader, "material.diffuse"), 0.0f, 1.0f, 0.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}