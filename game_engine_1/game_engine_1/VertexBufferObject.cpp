#include "VertexBufferObject.h"


VertexBufferObject::VertexBufferObject() {
	glGenBuffers(1, &this->id);
}


VertexBufferObject::~VertexBufferObject()
{
}

void VertexBufferObject::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->id);
}