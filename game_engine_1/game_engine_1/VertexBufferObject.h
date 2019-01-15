#pragma once

#include "gl.h"

class VertexBufferObject
{
public:
	GLuint id;
	
	VertexBufferObject();
	~VertexBufferObject();

	void bind();
};

