#pragma once

#include "gl.h"

#include <iostream>
#include <fstream>
#include <sstream>

class ShaderProgram
{
public:
	// the program ID
	unsigned int ID;

	// constructor reads and builds the shader
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	// use/activate the shader
	void use();
	// utility uniform functions
	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
};