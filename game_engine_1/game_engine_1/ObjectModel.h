#pragma once

#include "ShaderProgram.h"
#include "Camera.h"
#include "Texture.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

#include "gl.h"

class ObjectModel
{
public:
	float *assembledVertexArray;
	float *vertexCoord;
	float *vertexTexCoord;
	float *vertexColor;
	float *vertexNormalVec;
	int coordPos, texCoordPos, colorPos, normalVecPos;

	int stride;
	int vertexCount;
	int size;

	bool tex_model;

	VertexArrayObject *VAO;
	VertexBufferObject *VBO;
	Texture *texture;
	
	ObjectModel(int size, float *vertexes, int coordPos, int texCoordPos, int colorPos, int normalVecPos);
	ObjectModel(int size, float *vertexes, int coordPos, int texCoordPos, int colorPos, int normalVecPos, const char *vertexPath);
	~ObjectModel();

	void setVertexes(int size, float *vertexes, int coordPos, int texCoordPos, int colorPos, int normalVecPos);
	float *getVertexes();
	void setTexture(Texture *texture);
	void render(ShaderProgram *shaderProgram, Camera *camera, glm::mat4 model_matrix);

private:
	void configureModel();

};

