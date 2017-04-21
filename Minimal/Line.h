#pragma once

#include "Model.h"

class Line {
public:
	Line();
	void Draw(GLuint shader);

	glm::mat4 transform;

private:
	GLuint VAO, VBO;
};