#include "texture.h"

Texture::Texture() {}

Texture::Texture(std::string dir, std::string path, aiTextureType type)
	: dir(dir), path(path), type(type) {
	generate();
}

void Texture::generate() {
	glGenTextures(1, &id);
}

// load image, create texture and generate mipmaps
void Texture::load(bool flip) {
	// if true flip images vertically so that they are not upside down
	stbi_set_flip_vertically_on_load(flip);

	int width, height, nrChannels;

	unsigned char* data = stbi_load((dir + "/" + path).c_str(), &width, &height, &nrChannels, 0);

	GLenum colorMode = GL_RGB;

	switch (nrChannels) {
	case 1:
		colorMode = GL_RED;
		break;
	case 4:
		colorMode = GL_RGBA;
		break;
	}

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}
