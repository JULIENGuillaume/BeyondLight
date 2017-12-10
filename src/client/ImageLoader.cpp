//
// Created by diguie_t on 12/10/2017.
//

#include "ImageLoader.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb/stb_image.h"

namespace bl {
	bool ImageLoader::loadTexture(
			GLuint &res,
			const std::string &path,
			bool isAlpha
	) {
		res = 0;
		glGenTextures(1, &res);
		glBindTexture(GL_TEXTURE_2D, res);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// load and generate the texture
		int width;
		int height;
		int nrChannels;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			if (isAlpha) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			} else {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			}
			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			std::cerr << "Failed to load texture at: " << path << std::endl;
			stbi_image_free(data);
			return (true);
		}
		stbi_image_free(data);
		return (false);
	}

	bool ImageLoader::loadGlfwImage(
			GLFWimage *glfWimage,
			const std::string &path
	) {
		glfWimage->pixels = stbi_load(path.c_str(), &glfWimage->width, &glfWimage->height, nullptr, 0);
		return (glfWimage->pixels != nullptr);
	}
}