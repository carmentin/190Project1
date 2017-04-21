#pragma once

#include "Model.h"

class Line {
public:
	vector <float> coords;

	Line(vector <GLfloat> coords);

	void Draw(GLuint shader);

	glm::mat4 transform;

private:
	GLuint VAO, VBO;
};