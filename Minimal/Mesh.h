#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"


struct Vertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emission;
	float shininess;
};

class Mesh {
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;	
	Material mtl;

	/*  Functions  */
	// Constructor
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures, aiMaterial* mtl)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		aiColor3D ambient, diffuse, specular, emission;
		mtl->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
		mtl->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
		mtl->Get(AI_MATKEY_COLOR_SPECULAR, specular);
		mtl->Get(AI_MATKEY_COLOR_EMISSIVE, emission);
		this->mtl.ambient = glm::vec3(ambient.r, ambient.g, ambient.b);
		this->mtl.diffuse = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
		this->mtl.specular = glm::vec3(specular.r, specular.g, specular.b);
		this->mtl.emission = glm::vec3(emission.r, emission.g, emission.b);
		mtl->Get(AI_MATKEY_SHININESS, this->mtl.shininess);


		// Now that we have all the required data, set the vertex buffers and its attribute pointers.
		this->setupMesh();
	}

	void Draw(GLuint shader);

private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;

	void setupMesh();
};