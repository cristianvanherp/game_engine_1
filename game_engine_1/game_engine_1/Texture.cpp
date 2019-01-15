#include "Texture.h"

Texture::Texture(const char *img_path) {
	this->img_path = img_path;
	glGenTextures(1, &this->ID);
	this->configure();
}


Texture::~Texture()
{
}

void Texture::configure() {
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	unsigned char *image = stbi_load(this->img_path, &this->width, &this->height, &this->nrChannels, 0);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image); //Sets image for currently bound GL_TEXTURE_2D
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(image);
}

unsigned int Texture::get_id() {
	return this->ID;
}