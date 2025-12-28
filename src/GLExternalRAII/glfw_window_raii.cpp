#include "glfw_window_raii.h"
#include "GLExternalUtils/glfw_util.h"

namespace GLExternalRAII {
	Window::Window(int window_width, int window_height, int opengl_version_major, int opengl_version_minor) {
		glfw_window = GLExternalUtils::glfw_init(window_width, window_height, opengl_version_major, opengl_version_minor);
	}
	bool Window::is_running() const {
		return !glfwWindowShouldClose(glfw_window);
	}
	std::pair<int, int> Window::get_width_and_height() {
		int width{};
		int height{};
		glfwGetWindowSize(glfw_window, &width, &height);
		return { width, height };
	}
	void Window::frame_end() {
		GLExternalUtils::glfw_frame_end(glfw_window);
	}
	Window::~Window() {
		GLExternalUtils::glfw_destroy();
	}
}