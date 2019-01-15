#include "LightSource.h"



LightSource::LightSource(ObjectModel *model, glm::vec3 lightColor): Object(model)
{
	this->lightColor = lightColor;
}


LightSource::~LightSource()
{
}

void LightSource::render(ShaderProgram *shaderProgram, Camera *camera) {
	Object::render(shaderProgram, camera);
}
