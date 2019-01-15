#pragma once

#include "ObjectModel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Object
{
public:
	ObjectModel *model;
	glm::vec3 scale;
	glm::vec3 translation;
	float rotation_x, rotation_y, rotation_z;

	Object(ObjectModel *model);
	~Object();

	void render(ShaderProgram *shaderProgram, Camera *camera);
	void translate(glm::vec3 vector);
	
private:

};

