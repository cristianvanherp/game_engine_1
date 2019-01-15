#include "Object.h"

Object::Object(ObjectModel *model) {
	this->model = model;
	this->scale = glm::vec3(1.0f);
	this->rotation_x = this->rotation_y = this->rotation_z = 0.0f;
	this->translation = glm::vec3(0.0f);
}


Object::~Object()
{
}

void Object::translate(glm::vec3 vector) {
	this->translation += vector;
}

void Object::render(ShaderProgram *shaderProgram, Camera *camera) {
	shaderProgram->use();
	glm::mat4 model_matrix = glm::mat4(1.0);
	model_matrix = glm::rotate(model_matrix, glm::radians(this->rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(this->rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(this->rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::translate(model_matrix, this->translation);
	model_matrix = glm::scale(model_matrix, this->scale);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
	this->model->render(shaderProgram, camera, model_matrix);
}