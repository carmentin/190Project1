#include "Line.h"

Line::Line(vector <GLfloat> coords) {
	this->coords = coords;
	transform = glm::mat4(1.0f);

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->coords.size() * sizeof(GLfloat), &(this->coords[0]), GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat), (GLvoid*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::Draw(GLuint shader) {
	glUniform3f(glGetUniformLocation(shader, "material.diffuse"), 1.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shader, "material.specular"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader, "material.emission"), 1.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shader, "material.ambient"), 1.0f, 0.0f, 0.0f);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"), 16.f);

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}