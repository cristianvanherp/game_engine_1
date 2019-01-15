#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class LightSource: public Object
{
public:
	glm::vec3 lightColor;

	LightSource(ObjectModel *model, glm::vec3 lightColor);
	~LightSource();

	void render(ShaderProgram *shaderProgram, Camera *camera);
};

