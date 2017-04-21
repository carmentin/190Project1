#pragma once

#include "Model.h"

class Line {
public:
	Line();
	void Draw(GLuint shader);

private:
	GLuint VAO, VBO;
};