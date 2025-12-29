#include "glfw_window_raii.h"
#include "glfw_window_raii.h"
#include "glfw_window_raii.h"
#include "GLExternalUtils/glfw_util.h"

namespace GLExternalRAII {
	Window::Window(int window_width, int window_height, int opengl_version_major, int opengl_version_minor) {
		glfw_window = GLExternalUtils::glfw_init(window_width, window_height, opengl_version_major, opengl_version_minor);
		glfwSetWindowUserPointer(glfw_window, (void*)this);
		glfwSetKeyCallback(glfw_window, glfw_key_callback);
		glfwSetFramebufferSizeCallback(glfw_window, glfw_framebuffer_size_callback);
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
	void Window::glfw_framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
	{
		Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
		if (window->framebuffer_size_callback) {
			window->framebuffer_size_callback(width, height);
		}
	}
	void Window::glfw_key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
	{
		Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
		if (window->key_callback) {
			window->key_callback(key, scancode, action, mods);
		}
	}
	Window::~Window() {
		GLExternalUtils::glfw_destroy();
	}
}