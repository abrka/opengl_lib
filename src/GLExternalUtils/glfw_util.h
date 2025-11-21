#pragma once 

#include <cassert>
#include <GLFW/glfw3.h>

namespace GLExternalUtils {
	void glfw_error_callback(int error, const char* description) {
		fprintf(stderr, "[GLFW ERROR] %d: %s\n", error, description);
		assert(false);
	}

	GLFWwindow* glfw_init(int screen_width, int screen_height, int opengl_version_major, int opengl_version_minor) {
		glfwSetErrorCallback(glfw_error_callback);
		// glfw: initialize and configure
		// ------------------------------
		int ret = glfwInit();
		assert(ret == GLFW_TRUE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_version_major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_version_minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// glfw window creation
		// --------------------

		GLFWwindow* window =
			glfwCreateWindow(screen_width, screen_height, "OpenGL 3D Renderer", NULL, NULL);
		if (window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(-1);
		}
		glfwMakeContextCurrent(window);
		return window;
	}
	void glfw_frame_end(GLFWwindow* window)
	{
		// (Your code calls glfwSwapBuffers() etc.)

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
		// etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	void glfw_destroy()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}
}
