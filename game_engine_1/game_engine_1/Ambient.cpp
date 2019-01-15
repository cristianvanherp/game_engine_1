#include "Ambient.h"
#include <cstdlib>

Ambient::Ambient(ShaderProgram *shaderProgram)
{
	this->shaderProgram = shaderProgram;
	this->camera = new Camera();
	this->objects = std::vector<Object*>();
	this->lightSources = std::vector<LightSource*>();
}


Ambient::~Ambient()
{
}

void Ambient::add_object(Object *object) {
	this->objects.push_back(object);
}

void Ambient::add_light_source(LightSource *lightSource) {
	this->add_object((Object*)lightSource);
	this->lightSources.push_back(lightSource);
}

void Ambient::draw() {
	
	for (std::vector<LightSource*>::iterator i = this->lightSources.begin(); i != this->lightSources.end(); ++i) {
		this->shaderProgram->use();

		glUniform3fv(glGetUniformLocation(this->shaderProgram->ID, "lightPos"), 1, glm::value_ptr((*i)->translation));
		glUniform3fv(glGetUniformLocation(this->shaderProgram->ID, "lightColor"), 1, glm::value_ptr((*i)->lightColor));
	}

	for (std::vector<Object*>::iterator i = this->objects.begin(); i != this->objects.end(); ++i) {
		(*i)->render(this->shaderProgram, this->camera);
	}
}