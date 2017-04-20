#include "Mesh.h"

// Render the mesh
void Mesh::Draw(GLuint shader, glm::mat4 P, glm::mat4 V)
{
	glm::mat4 modelview = V * glm::mat4(1.0f);
	GLuint uProjection = glGetUniformLocation(shader, "projection");
	GLuint uModelview = glGetUniformLocation(shader, "modelview");
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, (&P[0][0]));
	glUniformMatrix4fv(uModelview, 1, GL_FALSE, &(V[0][0]));
	GLuint uTransMat = glGetUniformLocation(shader, "transMat");
	glUniformMatrix4fv(uTransMat, 1, GL_FALSE, &(glm::mat4(0.3, 0, 0, 0, 0, 0.3, 0, 0, 0, 0, 0.3, 0, 0, 5, -20, 1.0f)[0][0]));
	// Bind appropriate textures
	/*GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
										  // Retrieve texture number (the N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = this->textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		number = ss.str();
		// Now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(shader, (name + number).c_str()), i);
		// And finally bind the texture
		glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
	}*/

	// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
	aiColor3D diffuse, specular, ambient, emission;
	mtl->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
	mtl->Get(AI_MATKEY_COLOR_SPECULAR, specular);
	mtl->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
	mtl->Get(AI_MATKEY_COLOR_EMISSIVE, emission);
	glUniform3f(glGetUniformLocation(shader, "material.diffuse"), diffuse.r, diffuse.g, diffuse.b);
	glUniform3f(glGetUniformLocation(shader, "material.specular"), specular.r, specular.g, specular.b);
	glUniform3f(glGetUniformLocation(shader, "material.ambient"), ambient.r, ambient.g, ambient.b);
	glUniform3f(glGetUniformLocation(shader, "material.emission"), emission.r, emission.g, emission.b);
	float shininess;
	mtl->Get(AI_MATKEY_SHININESS, shininess);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"), shininess);

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	/*for (GLuint i = 0; i < this->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}*/
}

// Initializes all the buffer objects/arrays
void Mesh::setupMesh()
{
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}