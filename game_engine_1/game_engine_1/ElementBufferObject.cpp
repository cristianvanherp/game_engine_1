#include "ElementBufferObject.h"


ElementBufferObject::ElementBufferObject(int n) {
	glGenBuffers(n, this->ebo);
	this->last_index = n - 1;
}


ElementBufferObject::~ElementBufferObject()
{
}

void ElementBufferObject::insert(int n) {
	glGenBuffers(n, &this->ebo[this->last_index + 1]);
	this->last_index += n;
}

void ElementBufferObject::bind(int n) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo[n]);
}