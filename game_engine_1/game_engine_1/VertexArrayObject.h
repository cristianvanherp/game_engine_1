#pragma once

#include "gl.h"

class VertexArrayObject
{
public:
	GLuint id;

	VertexArrayObject();
	~VertexArrayObject();

	void bind();
};