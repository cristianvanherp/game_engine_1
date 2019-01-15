#pragma once

#include "gl.h"

class ElementBufferObject
{
public:
	GLuint ebo[512];
	int last_index;

	ElementBufferObject(int n);
	~ElementBufferObject();

	void insert(int n);
	void bind(int n);
};

