#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
	glGenVertexArrays(1, &this->id);
}


VertexArrayObject::~VertexArrayObject()
{
}

void VertexArrayObject::bind() {
	glBindVertexArray(this->id);
}