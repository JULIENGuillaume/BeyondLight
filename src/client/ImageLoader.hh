//
// Created by diguie_t on 12/10/2017.
//

#ifndef BEYONDLIGHT_IMAGELOADER_HH
#define BEYONDLIGHT_IMAGELOADER_HH

#include <string>
#include <iostream>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace bl {
	class ImageLoader {
	public:
		static bool loadTexture(
				GLuint &res,
				const std::string &path,
				bool isAlpha
		);
		static bool loadGlfwImage(
				GLFWimage *glfWimage,
				const std::string &path
		);
	};
}
#endif //BEYONDLIGHT_IMAGELOADER_HH
