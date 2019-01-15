#pragma once

#include "gl.h"
#include "stb_image.h"

#include <iostream>

class Texture
{
public:
	Texture(const char *img_path);
	~Texture();

	void configure();
	unsigned int get_id();

private:
	unsigned int ID;
	int width, height, nrChannels;
	const char *img_path;
};