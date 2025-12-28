#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace GLExternalUtils {
	static void glad_init()
	{
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(-1);
		}
	}
}