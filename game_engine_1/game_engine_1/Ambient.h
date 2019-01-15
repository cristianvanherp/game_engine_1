#pragma once

#include "Camera.h"
#include "LightSource.h"

#include <vector>

class Ambient
{
public:
	Camera *camera;
	ShaderProgram *shaderProgram;

	Ambient(ShaderProgram *shaderProgram);
	~Ambient();

	void add_object(Object *object);
	void add_light_source(LightSource *lightSource);
	void draw();

private:
	std::vector<Object*> objects;
	std::vector<LightSource*> lightSources;
};

