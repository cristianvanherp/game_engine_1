#include "Camera.h"

Camera::Camera() {
	this->upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	this->target = glm::vec3(0.0f, 0.0f, -1.0f);
	this->position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->speed = 5.0f;
	this->currentFrame = this->lastFrame = this->deltaTime = this->lastTime = 0.0f;
}

void Camera::setPositionX(double x) {
	this->position.x = x;
}

void Camera::setPositionY(double y) {
	this->position.y = y;
}

void Camera::setPositionZ(double z) {
	this->position.z = z;
}

void Camera::setTargetX(double x) {
	this->target.x = x;
}

void Camera::setTargetY(double y) {
	this->target.y = y;
}

void Camera::setTargetZ(double z) {
	this->target.z = z;
}

double Camera::getPositionX() {
	return this->position.x;
}

double Camera::getPositionY() {
	return this->position.y;
}

double Camera::getPositionZ() {
	return this->position.z;
}

double Camera::getTargetX() {
	return this->target.x;
}

double Camera::getTargetY() {
	return this->target.y;
}

double Camera::getTargetZ() {
	return this->target.z;
}

glm::vec3 Camera::getPosition() {
	return this->position;
}

glm::vec3 Camera::getTarget() {
	return this->target;
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
	this->position.y = 0.0f;
}

void Camera::setTarget(glm::vec3 target) {
	this->target = target;
}

void Camera::setSpeed(float speed) {
	this->speed = speed;
}

float Camera::getSpeed() {
	return this->speed;
}

void Camera::setCurrentSpeed(float currentSpeed) {
	this->currentSpeed = currentSpeed;
}

float Camera::getCurrentSpeed() {
	return this->currentSpeed;
}

void Camera::moveRight() {
	this->setPosition(this->getPosition() + glm::normalize(glm::cross(this->getTarget(), this->upVector)) * this->getCurrentSpeed());
}

void Camera::moveLeft() {
	this->setPosition(this->getPosition() - glm::normalize(glm::cross(this->getTarget(), this->upVector)) * this->getCurrentSpeed());
}

void Camera::moveUp() {

}

void Camera::moveDown() {

}

void Camera::moveFront() {
	this->setPosition(this->getPosition() + this->getTarget() * this->getCurrentSpeed());
}

void Camera::moveBack() {
	this->setPosition(this->getPosition() - this->getTarget() * this->getCurrentSpeed());
}

void Camera::update(float yaw, float pitch) {
	this->setTargetX(cos(glm::radians(pitch)) * cos(glm::radians(yaw)));
	this->setTargetY(sin(glm::radians(pitch)));
	this->setTargetZ(cos(glm::radians(pitch)) * sin(glm::radians(yaw)));
	
	//printf("%.2f %.2f %.2f\n", this->getTargetX(), this->getTargetY(), this->getTargetZ());
	
	this->setTarget(glm::normalize(this->getTarget()));
}

void Camera::adjustCameraSpeed(float time) {
	this->currentFrame = time;
	this->deltaTime = this->currentFrame - this->lastFrame;
	this->lastFrame = this->currentFrame;
	this->setCurrentSpeed(this->getSpeed() * this->deltaTime);
}


glm::mat4 Camera::lookAt() {
	return glm::lookAt(this->position, this->position + this->target, this->upVector);
}