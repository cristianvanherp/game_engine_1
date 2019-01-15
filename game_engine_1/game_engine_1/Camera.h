#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class Camera
{
public:
	Camera();

	glm::mat4 lookAt();
	void setPositionX(double x);
	void setPositionY(double y);
	void setPositionZ(double z);
	void setPosition(glm::vec3 position);

	void setTargetX(double x);
	void setTargetY(double y);
	void setTargetZ(double z);
	void setTarget(glm::vec3 target);

	double getPositionX();
	double getPositionY();
	double getPositionZ();
	glm::vec3 getPosition();

	double getTargetX();
	double getTargetY();
	double getTargetZ();
	glm::vec3 getTarget();

	float getSpeed();
	void setSpeed(float speed);

	float getCurrentSpeed();
	void setCurrentSpeed(float currentSpeed);

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void moveFront();
	void moveBack();

	void update(float yaw, float pitch);
	void adjustCameraSpeed(float time);

	float currentFrame, lastFrame, deltaTime, lastTime;

private:
	glm::vec3 front;
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 upVector;
	float currentSpeed;
	float speed;
};