#pragma once

#include "gl.h"
#include "GLhandler.h"
#include "ShaderProgram.h"
#include "Ambient.h"

#include <vector>

class Game
{
public:
	GLhandler *glHandler;
	Ambient *ambient;
	float lastX, lastY, yaw, pitch;
	bool running, firstMouse;

	static double xpos, ypos;
	
	Game();
	~Game();

	void setup();
	void start();
	void process_input(LightSource *lamp);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

};

