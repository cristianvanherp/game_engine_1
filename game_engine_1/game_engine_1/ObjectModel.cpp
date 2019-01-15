#include "ObjectModel.h"

ObjectModel::ObjectModel(int size, float *vertexes, int coordPos, int texCoordPos, int colorPos, int normalVecPos) {
	this->setVertexes(size, vertexes, coordPos, texCoordPos, colorPos, normalVecPos);
	this->configureModel();
	this->tex_model = false;
}

ObjectModel::ObjectModel(int vertexCount, float *vertexes, int coordPos, int texCoordPos, int colorPos, int normalVecPos, const char *texturePath) : ObjectModel(vertexCount, vertexes, coordPos, texCoordPos, colorPos, normalVecPos) {
	this->texture = new Texture(texturePath);
	this->tex_model = true;
}

ObjectModel::~ObjectModel()
{
}

void ObjectModel::setVertexes(int size, float *vertexes, int coordPos, int texCoordPos, int colorPos, int normalVecPos) {
	this->stride = 0;

	this->size = size;

	this->coordPos = coordPos;
	this->texCoordPos = texCoordPos;
	this->colorPos = colorPos;
	this->normalVecPos = normalVecPos;

	this->stride += (coordPos >= 0) ? 3 : 0;
	this->stride += (texCoordPos >= 0) ? 2 : 0;
	this->stride += (colorPos >= 0) ? 3 : 0;
	this->stride += (normalVecPos >= 0) ? 3 : 0;

	this->vertexCount = size / (4 * stride);

	if (coordPos >= 0) {
		this->vertexCoord = (float*)malloc(vertexCount * sizeof(float) * 3);
	}
	else {
		free(this->vertexCoord);
	}

	if (texCoordPos >= 0) {		
		this->vertexTexCoord = (float*)malloc(vertexCount * sizeof(float) * 3);
	}
	else {
		free(this->vertexTexCoord);
	}

	if (colorPos >= 0) {		
		this->vertexColor = (float*)malloc(vertexCount * sizeof(float) * 3);
	}
	else {
		free(this->vertexColor);
	}

	if (normalVecPos >= 0) {		
		this->vertexNormalVec = (float*)malloc(vertexCount * sizeof(float) * 3);
	}
	else {
		free(this->vertexNormalVec);
	}

	for (int i = 0; i < vertexCount; i++) {
		if (this->vertexCoord) {
			*(this->vertexCoord + (i * 3) + 0) = *(vertexes + (i * stride) + coordPos + 0);
			*(this->vertexCoord + (i * 3) + 1) = *(vertexes + (i * stride) + coordPos + 1);
			*(this->vertexCoord + (i * 3) + 2) = *(vertexes + (i * stride) + coordPos + 2);
		}
		
		if (this->vertexTexCoord) {
			*(this->vertexTexCoord + (i * 2) + 0) = *(vertexes + (i * stride) + texCoordPos + 0);
			*(this->vertexTexCoord + (i * 2) + 1) = *(vertexes + (i * stride) + texCoordPos + 1);
		}
		
		if (this->vertexColor) {
			*(this->vertexColor + (i * 3) + 0) = *(vertexes + (i * stride) + colorPos + 0);
			*(this->vertexColor + (i * 3) + 1) = *(vertexes + (i * stride) + colorPos + 1);
			*(this->vertexColor + (i * 3) + 2) = *(vertexes + (i * stride) + colorPos + 2);
		}
		
		if (this->vertexNormalVec) {
			*(this->vertexNormalVec + (i * 3) + 0) = *(vertexes + (i * stride) + normalVecPos + 0);
			*(this->vertexNormalVec + (i * 3) + 1) = *(vertexes + (i * stride) + normalVecPos + 1);
			*(this->vertexNormalVec + (i * 3) + 2) = *(vertexes + (i * stride) + normalVecPos + 2);
		}
	}

	this->assembledVertexArray = vertexes;
}

void ObjectModel::configureModel() {
	this->VAO = new VertexArrayObject();
	this->VBO = new VertexBufferObject();

	this->VAO->bind();
	this->VBO->bind();

	glBufferData(GL_ARRAY_BUFFER, this->size, this->assembledVertexArray, GL_STATIC_DRAW);

	if (this->vertexCoord) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, this->stride * sizeof(float), (void*)(this->coordPos * sizeof(float)));
		glEnableVertexAttribArray(0);
	}
	if (this->vertexTexCoord) {
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, this->stride * sizeof(float), (void*)(this->texCoordPos * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	if (this->vertexColor) {
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, this->stride * sizeof(float), (void*)(this->colorPos * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	if (this->vertexNormalVec) {
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, this->stride * sizeof(float), (void*)(this->normalVecPos * sizeof(float)));
		glEnableVertexAttribArray(3);
	}
}

float *ObjectModel::getVertexes() {
	return this->assembledVertexArray;
}

void ObjectModel::setTexture(Texture *texture) {
	this->texture = texture;
}

void ObjectModel::render(ShaderProgram *shaderProgram, Camera *camera, glm::mat4 model_matrix) {
	glm::mat4 view = camera->lookAt();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.01f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	if (this->vertexTexCoord) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->texture->get_id());
		glUniform1i(glGetUniformLocation(shaderProgram->ID, "tex"), 0);
	}

	glUniform1f(glGetUniformLocation(shaderProgram->ID, "ambient_lighting"), 0.4f);

	this->VAO->bind();
	GLfloat f;
	glGetUniformfv(shaderProgram->ID, glGetUniformLocation(shaderProgram->ID, "lightPosX"), &f);
	glGetUniformfv(shaderProgram->ID, glGetUniformLocation(shaderProgram->ID, "lightPosY"), &f);
	glGetUniformfv(shaderProgram->ID, glGetUniformLocation(shaderProgram->ID, "lightPosZ"), &f);
	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);
}