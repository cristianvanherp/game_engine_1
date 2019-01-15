#pragma once

#include "gl.h"

#include <iostream>

class GLhandler
{
public:
	GLhandler();
	~GLhandler();

	int init();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void set_mouse_callback(GLFWcursorposfun mouse_callback);
	GLFWwindow *getWindow();
	
private:
	GLFWwindow *window;
	GLFWcursorposfun mouse_callback;
};

