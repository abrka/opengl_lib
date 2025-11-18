#pragma once 

#include <GLFW/glfw3.h>

void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "[GLFW ERROR] %d: %s\n", error, description);
	assert(false);
}

GLFWwindow* glfw_init(int screen_width, int screen_height) {
	glfwSetErrorCallback(glfw_error_callback);
	// glfw: initialize and configure
	// ------------------------------
	int ret = glfwInit();
	assert(ret == GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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


void glfw_end()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

